//#################################################################################################
/*! \file M_LISTA.c
 *
 *  \brief Modulo da estrutura de lista
 *
 *  Interface responsavel pela implementacao dos metodos referentes a uma lista.
 */
//##################################################################################################

#include "../include/E_LISTA.h"
#include <stdlib.h>

#define M_LISTA


//--------------------------------------------------------------------------------------------------
Lista* inicializaNoLista(long pid){
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    
    lista->pid = pid;
    lista->page_faults = 0;
    lista->prox = NULL;
    
    return lista;
}


//--------------------------------------------------------------------------------------------------
void incPageFault(Lista** endereco_lista, long pid){
    
    //Se a lista estiver vazia, inicializamos um novo elemento e incrmentamos page faults
    if (*endereco_lista == NULL){
        *endereco_lista = inicializaNoLista(pid);
        (*endereco_lista)->page_faults++;
        return;
    }
    
    //Procuramos o elemento na lista
    Lista* l = *endereco_lista;
    do {
        if (l->pid == pid){ //Se encontrarmos o pid, incrementamos o numero de page faults
            l->page_faults++;
            return;
        }
        if(l->prox == NULL) break;
            
        l = l->prox;
    }
    while (1);
    
    //Se o pid nao foi encontrado, criamos um novo no
    l->prox = inicializaNoLista(pid);
    l->prox->page_faults++;
}


//--------------------------------------------------------------------------------------------------
char* ListaToString(Lista* lista){
    char* stringLista = "";
    
    //imprimimos a lista na string
    
    return stringLista;
}