//#################################################################################################
/*! \file I_SUBSPAG.h
 *
 *  \brief Interface do substituidor de paginas
 *
 *  Interface responsavel por disponibilizar servicos responsaveis pela substituicao de paginas
 *  do servidor de memoria.
 */
//##################################################################################################

#ifndef I_SUBSPAG_h
#define I_SUBSPAG_h

#ifdef M_SUBSPAG
#define EXT2
#else
#define EXT2 extern
#endif

#include "E_TABFRAMES.h"
#include "E_SEMAFORO.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por implementar os servicos relativos ao processo de substituicao de 
 * pagina na memoria.
 *
 * \param tab_frames Tabela de frames
 * \param semid id do conjunto de semaforos a ser utlizado
 * \return -1 se ocorreu erro
 */
EXT2 int servicoSubstuicaoPaginas(TabFrames* tab_frames, int semid);

#endif /* I_SUBSPAG_h */
