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
int servicoSubstuicaoPaginas(int msg_subs_id, int msg_aloc_id, TabFrames* tab_frames)
{
    
    Mensagem* msg;
    
    while (1) {
        //Recebe mensagem (ou aguarda até receber)
        
        //P(&solic_libera_pag); //Espera solicitacao de substituicao de paginas
        
        //Executa o servico de substituicao de pagina
        
        
        //V(&resp_libera_pag); //Notifica resultado ao alocador
        //V(&mutex)
        
        
    }
}