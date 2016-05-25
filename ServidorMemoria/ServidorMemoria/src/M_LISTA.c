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
void incPageFault(Lista** lista, long pid){
    
    //Se a lista estiver vazia, inicializamos um novo elemento e incrmentamos page faults
    if (*lista == NULL){
        *lista = inicializaNoLista(pid);
        (*lista)->page_faults++;
        return;
    }
    
    //Procuramos o elemento na lista
    Lista* l = *lista;
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
void imprimeLista(Lista* lista){
    int num_pf_total = 0;   //Numero de page faults totais
    Lista* lista_aux;
    
    lista_aux = lista;
    
    //Percorre cada noh da lista
    while(lista_aux != NULL){
        
        printf("/nNumero de page faults do processo %ld: %d", lista_aux->pid, lista_aux->page_faults);
        
        num_pf_total += lista->page_faults;
        lista_aux = lista_aux->prox;
    }
    
    printf("\nNumero de page faults total: %d", num_pf_total);
    
}