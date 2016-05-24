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
int servicoAlocacaoPaginas(int msg_aloc_id, int msg_user_id, TabFrames* tab_frames, int semid){
    Mensagem* msg;  
    
    
    V(semid, MUTEX); //Setamos mutex = 1
    
    while (1) {
        //Recebe mensagem (ou aguarda até receber)
        if (msgrcv(msg_aloc_id, msg, sizeof(Mensagem), 0, 0) < 0)
            return -1;
        
        printf("\n\nALOCADOR: Recebi msg de %ld com pag %d.\n", msg->pid, msg->num);
        
        P(semid, MUTEX); //Entra da secao critica
        
        //Verifica se a pagina i ja possui um page frame reservado
        //Se sim, nao ocorreu page fault
        if (buscaPagina(tab_frames, msg->num) >= 0){
            
            //Notificamos o usuario
            Mensagem* resposta = inicializaMensagem();
            resposta->pid = msg->pid;
            resposta->num = msg->num;
            msgsnd(msg_user_id, resposta, sizeof(Mensagem), 0);
        }
        //Se nao, houve um page fault
        else {
        
            //Verifica se o numero de paginas mapeadas atingiu MAX_OCUPACAO
            if (tab_frames->frames_ocupados >= MAX_OCUPACAO){
                
                //Se sim,
                V(semid, SOLIC_LIB_PAG); //Solicita liberacao de paginas
                
                V(semid, MUTEX); //Sai da secao critica
                
                P(semid, RESP_LIB_PAG); //Espera resposta do substituidor de paginas
                
                P(semid, MUTEX); //Entra da secao critica
            }
            
            //Uma frame livre eh escolhida aleatoriamente para mapear a pagina solicitada
           alocaPagina(tab_frames, msg->num);
            
            //Notificamos o usuario
            Mensagem* resposta = inicializaMensagem();
            resposta->pid = msg->pid;
            resposta->num = msg->num;
            msgsnd(msg_user_id, resposta, sizeof(Mensagem), 0);
            //TODO - SALVAR PAGE FAULTS EM UMA LISTA PARA FUTURA IMPRESSAO
        }
        
        V(semid, MUTEX); //Sai da secao critica
    }
}