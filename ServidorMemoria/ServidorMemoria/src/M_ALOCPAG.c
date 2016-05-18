//#################################################################################################
/*! \file M_ALOCPAG.c
 *
 *  \brief Modulo do alocador de paginas
 *
 *  Modulo responsavel por implementar os servicos responsaveis pela alocacao de paginas
 *  do servidor de memoria.
 */
//##################################################################################################

#include "../include/I_SUBSPAG.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define M_ALOCPAG


//--------------------------------------------------------------------------------------------------
int servicoAlocacaoPaginas(int msg_aloc_id, int msg_subs_id, TabFrames* tab_frames)
{
    Mensagem* msg;
    
    while (1) {
        //Recebe mensagem (ou aguarda até receber)
        if (msgrcv(msg_aloc_id, msg, sizeof(msg), 0, 0) < 0) return -1;
        
        //P(&mutex)
        //1. Verifica se a pagina i ja possui um page frame reservado
        
        //1.1. Se sim, nao ocorreu page fault
        //Atualizamos dados de tempo de referencia
        //V(&mutex)
        
        //--------------------------------------------------
        //1.2. Se nao, houve um page fault
        
        //1.2.1. Verifica se o numero de paginas mapeadas atingiu MAX_OCUPACAO
        //1.2.1.1 Se sim,
        //V(&solic_libera_pag); //Solicita substituicao de paginas
        //V(&mutex)
        //P(&resp_libera_pag); //Espera resposta do substituidor de paginas
        
        //1.2.1.2 Se nao, uma frame livre eh escolhida aleatoriamente para mapear
        //a pagina i
        //V(&mutex)
        
        
        
    }
}