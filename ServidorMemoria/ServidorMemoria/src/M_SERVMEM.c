//#################################################################################################
/*! \file M_SERVMEM.c
 *
 *  \brief Modulo de Inicializacao do servidor de memória.
 *
 *  Modulo responsavel por implementar os metodos relacionados a inicializacao de estruturas e
 * a execucao do servidor de memoria. Eh responsavel pela alocacao e substituicao de paginas.
 */
//##################################################################################################


#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "../include/I_SUBSPAG.h"
#include "../include/I_ALOCPAG.h"
#include "../include/E_MENSAGEM.h"
#include "../include/E_TABFRAMES.h"
#include "../include/I_SEMAFORO.h"


//--------------------------------------------------------------------------------------------------
// Variaveis Globais
int pid;

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por encerrar o servidor de memoria
 */
void encerraServidor()
{
    int estado; //Estado de encerramento do processo filho
    
    printf("Encerrando servidor...\n");
    
    //Se for o filho, encerramos
    if (pid == 0) exit(0);
    
    //Encerramos o processo filho
    kill(pid, SIGKILL);
    wait(&estado);
    
    //Encerramos o processo atual
    exit(0);
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo inicial do sistema
 *
 */
int main(int argc, const char * argv[])
{
    
//    int msg_aloc_id, msg_subs_id;
//    TabFrames* tabFrames;
//    
//    //Se receber a notificacao de encerramento, desviamos para a rotina de termino.
//    signal(SIGUSR1, encerraServidor);
//    
//    //Inicializamos a tabela de frames
//    tabFrames = inicializaTabFrames();
//    
//    
//    //Criacao das filas de mensagens dos processos de alocacao e substituicao de paginas
//    msg_aloc_id = msgget(KEY_T0, IPC_CREAT | 0x1FF);
//    msg_subs_id = msgget(KEY_T1, IPC_CREAT | 0x1FF);
//    
//    //Verificamos se houve erro na criacao das filas de mensagens
//    if (msg_subs_id < 0 || msg_aloc_id < 0) {
//        printf("Erro na criacao de filas de mensagem. Encerrando servidor\n");
//        exit(1);
//    }
//    
//    //Criamos um novo processo
//    pid = fork();
//    
//    //O processo de substituicao de paginas serah o processo filho
//    if (pid == 0) servicoSubstuicaoPaginas(msg_subs_id, msg_aloc_id, tabFrames);
//    
//    //Execucao do processo de alocacao de paginas
//    else servicoAlocacaoPaginas(msg_aloc_id, msg_subs_id, tabFrames);
//    
//    return 0;
    
    int pid, semid, estado, respostaP, respostaV;
    // P(sem);
    if((semid = inicializaSemaforo(0x1223, 1, 1)) < 0)
    {
        printf("Erro na criacao do semaforo\n");
        exit(1);
    }
    printf("\nCriacao do semaforo do identificador %d\n",semid) ;
    
    //pid = fork();
    
    if ((pid = fork()) < 0) {
        printf("erro ao criar o processo filho");
    }
    
    if (pid == 0) {
        printf("\tEu sou o FILHO e vou fazer P sobre o semaforo\n");
        //respostaP = P(semid,0);
        if((respostaP = P(semid,0)) < 0) printf("erro no p_filho = %d\n", errno);
        printf("\tEu sou o FILHO e vou dormir 10 segundos...\n") ;
        sleep(10) ;
        printf("\tEu sou o FILHO e vou fazer V sobre o semaforo\n") ;
        //respostaV = V(semid, 0);
        if((respostaV = V(semid, 0)) < 0) printf("erro no v_filho = %d\n", errno);
        sleep(1);
        exit(0);
    }
    else {
        printf("Eu sou o PAI e vou dormir 2 segundos...\n") ;
        sleep(2);
        printf("Eu sou o PAI e vou me bloquear fazendo P sobre o semaforo\n");
        //respostaP = P(semid, 0) ;
        if((respostaP = P(semid, 0)) < 0) printf("erro no p_pai = %d\n", errno);
        printf("Eu sou o PAI e acabei de me desbloquear\n") ;
        if (removeSemaforo(semid) < 0) printf("Erro na destruicao do semaforo");
        printf("Eu sou o PAI e vou acabar o processamento\n\n");
        wait(&estado);
        exit(0);
    }
}
