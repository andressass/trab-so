//#################################################################################################
/*! \file E_LISTA.h
 *
 *  \brief Interface da estrutura de lista
 *
 *  Interface responsavel pela definicao de estruturas e metodos referentes a uma lista.
 */
//##################################################################################################

#ifndef E_LISTA_h
#define E_LISTA_h

#ifdef M_LISTA
#define EXT6
#else
#define EXT6 extern
#endif


//--------------------------------------------------------------------------------------------------
// Estruturas
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//! Estrutura de lista
/*!
 * Estrura que representa um noh de lista.
 */
typedef struct lista {
    long pid; //!< PID do processo usuario
    int page_faults; //!< Numero de page faults do processo
    struct lista *prox; //!< Proximo Elemento da lista
} Lista;


//--------------------------------------------------------------------------------------------------
// Metodos
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por inicializar e retornar uma estrutura de um no de lista.
 *
 * \param pid pid do novo no
 * \return Estrutura de lista inicializada
 */
EXT6 Lista* inicializaNoLista(long pid);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por incrementar o numero de page faults de um processo na lista. Caso o pid do
 * processo nao esteja na lista, um novo no eh criado.
 *
 * \param lista Endereco da lista contendo os page faults dos processos
 * \param pid Id do processo a ter o numero de page faults incrementado
 *
 * \return Estrutura de lista inicializada
 */
EXT6 void incPageFault(Lista** lista, long pid);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por retornar um array de caracteres que representa a impressao dos dados 
 * contidos na lista.
 *
 * \param lista Lista a ser convertida
 * \return Array de caracteres que representa os dados de uma lista
 */
EXT6 char* ListaToString(Lista* lista);



#endif /* E_LISTA_h */
