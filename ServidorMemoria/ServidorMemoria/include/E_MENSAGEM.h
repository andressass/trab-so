//#################################################################################################
/*! \file E_MENSAGEM.h
 *
 *  \brief Interface de estrutura de mensagens
 *
 *  Interface responsavel pela definicao da estrutura de mensagens utilizadas na fila de mensagens para a comunicação entre processos.
 */
//##################################################################################################

#ifndef E_MENSAGEM_h
#define E_MENSAGEM_h

#ifdef M_MENSAGEM
#define EXT3
#else
#define EXT3 extern
#endif


#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//--------------------------------------------------------------------------------------------------
// Definicoes
//--------------------------------------------------------------------------------------------------

#define KEY_T0 0x398801 //!< Chave para a fila de mensagens do processo de alocacao de memoria
#define KEY_T1 0x539712 //!< Chave para a fila de mensagens do processo de substituicao de paginas

//--------------------------------------------------------------------------------------------------
// Estruturas
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//! Estrutura de mensagem
/*!
 * Estrura que representa uma mensagem de comunicacao entre processos.
 */
typedef struct mensagem{
    int pid; //<! pid do processo que enviou a mensagem
    int num_pagina; //!< Numero da pagina
    short tipo; //!< 0 para solicitacao e 1 para notificacao
} Mensagem;


//--------------------------------------------------------------------------------------------------
// Metodos
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por inicializar e retornar uma estrutura de mensagem
 *
 * \return Estrutura de mensagem inicializada
 */
EXT3 Mensagem* inicializaMensagem();

#endif /* E_MENSAGEM_h */
