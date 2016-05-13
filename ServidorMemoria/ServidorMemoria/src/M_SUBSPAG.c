//#################################################################################################
/*! \file M_SUBSPAG.c
 *
 *  \brief Modulo do substituidor de paginas
 *
 *  Modulo responsavel por implementar os servicos responsaveis pela substituicao de paginas
 *  do servidor de memoria.
 */
//##################################################################################################

#include "../include/I_SUBSPAG.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define M_SUBSPAG


//--------------------------------------------------------------------------------------------------
int servicoSubstuicaoPaginas(int msg_subs_id, int msg_aloc_id, TabFrames* tab_frames){
    
    Mensagem* msg;
    
    while (1) {
        //Recebe mensagem (ou aguarda até receber)
        if (msgrcv(msg_subs_id, msg, sizeof(msg), 0, 0) < 0) return -1;
        
        //Executa o servico de substituicao de pagina
        
        //Notifica conclusao ao alocador
    }
}