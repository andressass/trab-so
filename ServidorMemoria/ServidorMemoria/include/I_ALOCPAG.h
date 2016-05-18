//#################################################################################################
/*! \file I_ALOCPAG.h
 *
 *  \brief Interface do alocador de paginas
 *
 *  Interface responsavel por disponibilizar servicos responsaveis pela alocacao de paginas
 *  do servidor de memoria.
 */
//##################################################################################################

#ifndef I_ALOCPAG_h
#define I_ALOCPAG_h

#ifdef M_ALOCPAG
#define EXT1
#else
#define EXT1 extern
#endif


#include "E_MENSAGEM.h"
#include "E_TABFRAMES.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por implementar os servicos relativos ao processo de alocacao de paginas da
 * memoria. Ele espera uma solicitacao atraves de uma fila de mensagens e executa o servico 
 * solicitado.
 *
 * \param msg_aloc_id id da fila de mensagens de entrada do alocador
 * \param msg_subs_id id da fila de mensagens de entrada do substiuidor de paginas
 * \param tab_frames Tabela de frames
 * \return -1 se ocorreu erro
 */
EXT1 int servicoAlocacaoPaginas(int msg_aloc_id, int msg_subs_id, TabFrames* tab_frames);

#endif /* I_ALOCPAG_h */
