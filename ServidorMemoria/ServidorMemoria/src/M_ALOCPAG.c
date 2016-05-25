//#################################################################################################
/*! \file M_ALOCPAG.c
 *
 *  \brief Modulo do alocador de paginas
 *
 *  Modulo responsavel por implementar os servicos responsaveis pela alocacao de paginas
 *  do servidor de memoria.
 */
//##################################################################################################

#include "../include/I_ALOCPAG.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <stdio.h>

#define M_ALOCPAG


//--------------------------------------------------------------------------------------------------
// Variaveis globais
//--------------------------------------------------------------------------------------------------

int _shmid; //!< id da area de memoria compartilhada da tabela de frames
int _semid; //!< id do conjunto semaforos;

int _msg_aloc_id; //!< id das filas de mensagem de entrada do alocador
int _msg_user_id; //!< id das filas de mensagem de notificacao dos usuarios

TabFrames* _tab_frames; //!< ponteiro para a tabela de frames
Lista* _lista_resultados; //!< ponteiro a para lista que armazena o numero de page faults por pid


//--------------------------------------------------------------------------------------------------
// Metodos
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por encerrar o alocador de paginas
 */
void encerraAlocador()
{
    int estado; //Estado de encerramento do processo filho
    
    printf("Encerrando servidor...\n");
    
    //Imprimimos os resultados e estado atual da tabela de frames
    imprimeLista(_lista_resultados);
    imprimeTabFrames(_tab_frames);
    
    //Esperamos o processo Substituidor de pag
    wait(&estado);
    
    //Liberamos a tabela de frames
    removeTabFrames(_shmid, _tab_frames);
    
    //Liberamos os semaforos
    removeConjSemaforo(_semid);
    
    //Liberamos a fila de mensagens
    msgctl(_msg_user_id, IPC_RMID, 0);
    msgctl(_msg_aloc_id, IPC_RMID, 0);
    
    //Encerramos o processo atual
    exit(0);
}



//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por implementar os servicos relativos a busca de paginas em uma tabela de
 * frames
 *
 * \param tab_frames Tabela de frames
 * \param pag_num numero da pagina
 * \return Numero do frame, caso encontre a pagina; -1, se ocorreu page fault
 */
int buscaPagina(TabFrames* tab_frames, int pag_num){
    for(int i = 0; i < NUMERO_FRAMES; i++)
        if(tab_frames->frames[i].num_pag == pag_num){
            
            //Atualizamos o tempo de referencia
            tab_frames->frames[i].tempo_ref = clock();
            
            //Retornamos o numero do frame
            return i;
        }
    return -1; //Page fault
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por implementar os servicos relativos a alocaco de paginas em uma tabela de
 * frames
 *
 * \param tab_frames Tabela de frames
 * \param pag_num numero da pagina
 * \return Numero do frame, caso encontre a pagina; -1, se ocorreu page fault
 */
int alocaPagina(TabFrames* tab_frames, int pag_num){
    for(int i = 0; i < NUMERO_FRAMES; i++)
        //Se o frame estiver livre (-1)
        if(tab_frames->frames[i].num_pag == -1){
            //Alocamos a pagina
            tab_frames->frames[i].num_pag = pag_num;
            tab_frames->frames[i].tempo_ref = clock();
            tab_frames->frames_ocupados++;
        
            //Retornamos o numero do frame
            return i;
        }
    return -1;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por implementar o loop principal com as funcionalidades do alocador de paginas
 *
 * \return  -1, se ocorreu erro;
 */
int rotinaAlocacaoPaginas(){
    //Inicializamos a estrutura que receberah as mensagens
    Mensagem* msg = inicializaMensagem();
    
    V(_semid, MUTEX); //Setamos mutex = 1
    
    while (1) {
        //Recebe mensagem (ou aguarda até receber)
        if (msgrcv(_msg_aloc_id, msg, sizeof(Mensagem), 0, 0) < 0)
            return -1;
        
        printf("\nP: %ld\t Pag %d.", msg->pid, msg->num);
        
        P(_semid, MUTEX); //Entra da secao critica
        
        //Verifica se a pagina i ja possui um page frame reservado
        //Se sim, nao ocorreu page fault
        if (buscaPagina(_tab_frames, msg->num) >= 0){
            
            //Notificamos o usuario
            Mensagem* resposta = inicializaMensagem();
            resposta->pid = msg->pid;
            resposta->num = msg->num;
            msgsnd(_msg_user_id, resposta, sizeof(Mensagem), 0);
        }
        //Se nao, houve um page fault
        else {
            
            //Verifica se o numero de paginas mapeadas atingiu MAX_OCUPACAO
            if (_tab_frames->frames_ocupados >= MAX_OCUPACAO){
                
                //Se sim,
                V(_semid, SOLIC_LIB_PAG); //Solicita liberacao de paginas
                
                V(_semid, MUTEX); //Sai da secao critica
                
                P(_semid, RESP_LIB_PAG); //Espera resposta do substituidor de paginas
                
                P(_semid, MUTEX); //Entra da secao critica
            }
            
            //Uma frame livre eh escolhida aleatoriamente para mapear a pagina solicitada
            alocaPagina(_tab_frames, msg->num);
            
            //Notificamos o usuario
            Mensagem* resposta = inicializaMensagem();
            resposta->pid = msg->pid;
            resposta->num = msg->num;
            msgsnd(_msg_user_id, resposta, sizeof(Mensagem), 0);
            
            
            //Incrementamos o numero de page faults na lista de resultados
            incPageFault(&_lista_resultados, msg->pid);
            printf("\nPage Fault!");
        }
        
        V(_semid, MUTEX); //Sai da secao critica
    }
}


//--------------------------------------------------------------------------------------------------
int servicoAlocacaoPaginas(TabFrames* tab_frames, int semid, int shmid){
    
    _tab_frames = tab_frames;
    _semid = semid;
    _shmid = shmid;
    
    //Se receber a notificacao de encerramento, desviamos para a rotina de termino.
    signal(SIGUSR1, encerraAlocador);
    
    //Criacao das filas de mensagens dos processos de alocacao e substituicao de paginas
    _msg_aloc_id = msgget(KEY_T0, IPC_CREAT | 0x1FF);
    _msg_user_id = msgget(KEY_T1, IPC_CREAT | 0x1FF);
    
    //Verificamos se houve erro na criacao das filas de mensagens
    if (_msg_user_id < 0 || _msg_aloc_id < 0) {
        printf("Erro na criacao de filas de mensagem. Encerrando servidor...\n");
        exit(1);
    }
    
    //Chamamos a rotina de alocacao de paginas
    rotinaAlocacaoPaginas();
    
    encerraAlocador();
    
    return -1;
}