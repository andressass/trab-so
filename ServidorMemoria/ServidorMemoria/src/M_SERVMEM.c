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
#include "../include/E_SEMAFORO.h"


//--------------------------------------------------------------------------------------------------
// Variaveis Globais
int pid; //!< id do processo atual

int msg_aloc_id; //!< id das filas de mensagem de entrada do alocador
int msg_usu_id; //!< id das filas de mensagem de notificacao dos usuarios
int shmid; //!< id da area de memoria compartilhada da tabela de frames
int semid; //!< id do conjunto semaforos;

TabFrames* tabFrames; //!< ponteiro para a tabela de frames

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
    
    //Liberamos a tabela de frames
    removeTabFrames(shmid, tabFrames);
    
    //Liberamos os semaforos
    removeConjSemaforo(semid);
    
    //Liberamos a fila de mensagens
    msgctl(msg_usu_id, IPC_RMID, 0);
    msgctl(msg_aloc_id, IPC_RMID, 0);
    
    //TODO - IMPRIMIR DADOS DO ESTADO ATUAL DO PROGRAMA (LISTA DE PAGE_FAULTS E TABELA)
    
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
    
    
    //Se receber a notificacao de encerramento, desviamos para a rotina de termino.
    signal(SIGUSR1, encerraServidor);
    
    //Criamos e inicializamos a tabela de frames
    if ((shmid = inicializaTabFrames(KEY_TAB0, &tabFrames)) < 0)
        printf("Erro ao criar tabela de frames.Encerrando servidor...\n");
    
    //Criacao das filas de mensagens dos processos de alocacao e substituicao de paginas
    msg_aloc_id = msgget(KEY_T0, IPC_CREAT | 0x1FF);
    msg_usu_id = msgget(KEY_T1, IPC_CREAT | 0x1FF);
    
    //Verificamos se houve erro na criacao das filas de mensagens
    if (msg_usu_id < 0 || msg_aloc_id < 0) {
        printf("Erro na criacao de filas de mensagem. Encerrando servidor...\n");
        exit(1);
    }
    
    //Criacao do conjunto de semaforos
    if ((semid = inicializaConjSemaforo(KEY_SEM0, NSEMS, 0)) < 0)
        printf("Erro na criacao dos semaforos. Encerrando servidor...\n");;
    
    //Criamos um novo processo
    pid = fork();
    
    //O processo de substituicao de paginas serah o processo filho
    if (pid == 0) servicoSubstuicaoPaginas(tabFrames, semid);
    
    //Execucao do processo de alocacao de paginas
    else servicoAlocacaoPaginas(msg_aloc_id, msg_usu_id, tabFrames, semid);
    
    return 0;
    
}
