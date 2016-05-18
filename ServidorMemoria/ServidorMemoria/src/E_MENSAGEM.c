//#################################################################################################
/*! \file M_ALOCPAG.c
 *
 *  \brief Modulo de estrutura de mensagens
 *
 *  Modulo responsavel por implementar os metodos relacionados as estruturas de mensagens utilizadas na fila de mensagens para a comunicação entre processos.
 */
//##################################################################################################

#include "../include/E_MENSAGEM.h"

#define M_MENSAGEM


//--------------------------------------------------------------------------------------------------
Mensagem* inicializaMensagem()
{

    Mensagem* mensagem;
    
    //TODO - Criar area de ememoria compartilhada para armazenar a tabela
    mensagem = (Mensagem*) malloc(sizeof(Mensagem));
    mensagem->pid = -1;
    mensagem->num_pagina = -1;
    mensagem->tipo = -1;
    
    return mensagem;
}
