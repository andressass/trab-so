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
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>

#include "../include/I_SUBSPAG.h"
#include "../include/I_ALOCPAG.h"
#include "../include/ESTRUTURAS.h"

//--------------------------------------------------------------------------------------------------
// Variaveis Globais
int pid;

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por encerrar o servidor de memoria
 */
void encerraServidor(){
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
int main(int argc, const char * argv[]) {
    
    int msg_aloc_id, msg_subs_id;
    TabFrames* tabFrames;
    
    //Se receber a notificacao de encerramento, desviamos para a rotina de termino.
    signal(SIGUSR1, encerraServidor);
    
    //Inicializamos a tabela de frames
    //TODO - Criar area de ememoria compartilhada para armazenar a tabela
    tabFrames = (TabFrames*) malloc(sizeof(TabFrames));
    tabFrames->frames = (Frame*) malloc(NUMERO_FRAMES * sizeof(Frame));
    tabFrames->frames_livres = 0;
    
    //Criacao das filas de mensagens dos processos de alocacao e substituicao de paginas
    msg_aloc_id = msgget(KEY_T0, IPC_CREAT | 0x1FF);
    msg_subs_id = msgget(KEY_T1, IPC_CREAT | 0x1FF);
    
    //Verificamos se houve erro na criacao das filas de mensagens
    if (msg_subs_id < 0 || msg_aloc_id < 0) {
        printf("Erro na criacao de filas de mensagem. Encerrando servidor\n");
        exit(1);
    }
    
    //Criamos um novo processo
    pid = fork();
    
    //O processo de substituicao de paginas serah o processo filho
    if (pid == 0) servicoSubstuicaoPaginas(msg_subs_id, msg_aloc_id, tabFrames);
    
    //Execucao do processo de alocacao de paginas
    else servicoAlocacaoPaginas(msg_aloc_id, msg_subs_id, tabFrames);
    
    return 0;
}
