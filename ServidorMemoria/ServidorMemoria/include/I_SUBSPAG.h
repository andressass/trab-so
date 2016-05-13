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


#include "ESTRUTURAS.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por implementar os servicos relativos ao processo de substituicao de 
 * pagina na memoria. Ele espera uma solicitacao atraves de uma fila de mensagens e executa o 
 * servico solicitado.
 *
 * \param msg_subs_id id da fila de mensagens de entrada do substiuidor de paginas
 * \param msg_aloc_id id da fila de mensagens de entrada do alocador
 * \param tab_frames Tabela de frames
 * \return -1 se ocorreu erro
 */
int servicoSubstuicaoPaginas(int msg_subs_id, int msg_aloc_id, TabFrames* tab_frames);

#endif /* I_SUBSPAG_h */
