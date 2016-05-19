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

#include "../include/E_MENSAGEM.h"


//--------------------------------------------------------------------------------------------------
// Variaveis Globais
int pid; //!< id do processo atual

int msg_aloc_id; //!< id das filas de mensagem de entrada do alocador
int msg_usu_id; //!< id das filas de mensagem de notificacao dos usuarios




//--------------------------------------------------------------------------------------------------
/*!
 * Metodo inicial do sistema
 *
 */
int main(int argc, const char * argv[])
{
    
    //Obtencao das filas de mensagens dos processos de alocacao e substituicao de paginas
    msg_aloc_id = msgget(KEY_T0, 0x1FF);
    msg_usu_id = msgget(KEY_T1, 0x1FF);
    
    //Verificamos se houve erro na criacao das filas de mensagens
    if (msg_usu_id < 0 || msg_aloc_id < 0) {
        printf("Erro na obtencao das filas de mensagem. Encerrando servidor...\n");
        exit(1);
    }
    
    Mensagem* m1 = inicializaMensagem();
    
    //Referencia pagina
    
    for (int i = 0; i < 20; i++) {
        m1->pid = getpid();
        m1->num = i%10;
        if(msgsnd(msg_aloc_id, m1, sizeof(Mensagem), 0) < 0)
            printf("Erro de envio mensagem\n\n");
        
    }
    
    for (int i = 0; i < 20; i++){
        if(msgrcv(msg_usu_id, m1, sizeof(Mensagem), getpid(), 0) < 0)
            printf("Erro de recebimento de mensagem\n\n");
        else printf("\n\nUSUARIO: Recebi mensagem!!\n\n");
    }
    
    return 0;
    
}
