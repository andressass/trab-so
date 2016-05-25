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
#include "../include/E_TABFRAMES.h"
#include "../include/E_SEMAFORO.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por criar os processos do alocador e do substituidor de paginas e as 
 * estruturas compartilhadas entre eles.
 *
 */
int main(int argc, const char * argv[])
{
    int pid; //!< id do processo atual
    int shmid; //!< id da area de memoria compartilhada da tabela de frames
    int semid; //!< id do conjunto semaforos;
    TabFrames* tabFrames; //!< ponteiro para a tabela de frames
    
    //Criamos e inicializamos a tabela de frames
    if ((shmid = inicializaTabFrames(KEY_TAB0, &tabFrames)) < 0){
        printf("Erro ao criar tabela de frames.Encerrando servidor...\n");
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
    else servicoAlocacaoPaginas(tabFrames, semid, shmid);
    
}
