//#################################################################################################
/*! \file I_SUBSPAG.h
 *
 *  \brief Interface de estruturas do sistema
 *
 *  Interface responsavel pela definicao de estruturas de uso comum do sistema
 */
//##################################################################################################

#ifndef ESTRUTURAS_h
#define ESTRUTURAS_h

//--------------------------------------------------------------------------------------------------
// Definicoes
//--------------------------------------------------------------------------------------------------

#define KEY_T0 971880 //!< Chave para a fila de mensagens do processo de alocacao de memoria
#define KEY_T1 100398 //!< Chave para a fila de mensagens do processo de substituicao de paginas

#define NUMERO_FRAMES 10
#define MAX_OCUPACAO 9
#define OCUPACAO_OK 8


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
//! Estrutura de mensagem
/*!
 * Estrura que representa uma linha da tabela de paginas.
 */
typedef struct frame{
    int numero; //!< Numero da pagina
    int tempo_ref; //!< Tempo de referencia da pagina
    short reservada; //!< Lock para seber se a pagina estah bloqueada ou nao
} Frame;


//--------------------------------------------------------------------------------------------------
//! Estrutura de mensagem
/*!
 * Estrura que representa uma tabela de frames
 */
typedef struct tabelaFrames{
    Frame* frames;
    int frames_livres;
} TabFrames;


#endif /* ESTRUTURAS_h */
