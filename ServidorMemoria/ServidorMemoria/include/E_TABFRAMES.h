//#################################################################################################
/*! \file E_TABFRAMES.h
 *
 *  \brief Interface de estrutura da tabela de frames
 *
 *  Interface responsavel pela definicao da estrutura da tabela de frames.
 */
//##################################################################################################

#ifndef E_TABFRAMES_h
#define E_TABFRAMES_h

#ifdef M_TABELAFRAMES
#define EXT4
#else
#define EXT4 extern
#endif


#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include "E_LISTA.h"

//--------------------------------------------------------------------------------------------------
// Definicoes
//--------------------------------------------------------------------------------------------------

#define NUMERO_FRAMES 10 //!< Numero total de frames da tabela
#define MAX_OCUPACAO 9 //!< Numero maximo de frames que podem ocupar a sem uma liberacao
#define OCUPACAO_OK 8 //!< Numero de frames em caso de liberacao de pafinas

#define KEY_TAB0 0x398571 //!<Chave para a tabela de frames

//--------------------------------------------------------------------------------------------------
//! Estrutura de frame
/*!
 * Estrura que representa uma linha da tabela de paginas.
 */
typedef struct frame{
    int num_pag; //!< Numero da pagina
    clock_t tempo_ref; //!< Tempo de referencia da pagina
} Frame;


//--------------------------------------------------------------------------------------------------
//! Estrutura de tabela de frames
/*!
 * Estrura que representa uma tabela de frames
 */
typedef struct tabelaFrames{
    Frame frames[NUMERO_FRAMES];
    int frames_ocupados;
    int num_exec_proc_subst;
} TabFrames;


//--------------------------------------------------------------------------------------------------
// Metodos
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por inicializar e retornar uma estrutura de tabela de frames em uma area
 * compartilhada de memoria.
 *
 * \param chave Chave para a criacao da area de memoria compartilhada
 * \param tabFrames ponteiro que vai receber o endereco da tabela de paginas
 * \return id da area de memoria compartilhada
 */
EXT4 int inicializaTabFrames(int chave, TabFrames** tabFrames);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por remover uma area de memoria compartilhada que contem uma tabela de frames
 *
 * \param shmid id da area de memoria comparilhada
 * \param tabFrames ponteiro para a tabela de paginas
 * \return 0, em caso de sucesso, -1, em caso de erro
 */
EXT4 int removeTabFrames(int shmid, TabFrames* tabFrames);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por retornar um array de caracteres que representa a impressao dos dados
 * contidos na tabela de frames.
 *
 * \param tabFrames TabFrames a ser impressa
 */
EXT4 void imprimeTabFrames(TabFrames* tabFrames);


#endif /* E_TABFRAMES_h */
