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
int servicoAlocacaoPaginas(int msg_aloc_id, int msg_subs_id, TabFrames* tab_frames){
    Mensagem* msg;
    
    while (1) {
        //Recebe mensagem (ou aguarda até receber)
        if (msgrcv(msg_aloc_id, msg, sizeof(msg), 0, 0) < 0) return -1;
        
        //Se a mensagem for de solicitacao
        //Executa o servico de alocacao
        //aloca_pagina(msg->pid, msg->pag)
        
        //Se a mensagem for de notificacao
        //respondemos ao processo que a alocacao estah completa
        
        
    }
}