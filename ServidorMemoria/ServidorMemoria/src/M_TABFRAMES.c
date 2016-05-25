//#################################################################################################
/*! \file M_TABFRAMES.c
 *
 *  \brief Modulo de estrutura de tabela de frames
 *
 *  Modulo responsavel por implementar os metodos relacionados as tabelas de frames
 */
//##################################################################################################

#include "../include/E_TABFRAMES.h"

#define M_TABFRAMES


//--------------------------------------------------------------------------------------------------
int inicializaTabFrames(key_t chave, TabFrames** tabFrames){
    
    int idshm;
    
    //Criamos a area de memoria compartilhada para armazenar a tabela
    idshm = shmget(chave, sizeof(TabFrames), IPC_CREAT | 0644);
    if (idshm < 0) return -1;

    //Mapeamos a estrutura na memoria
    if((*tabFrames = (TabFrames*)shmat(idshm, 0, 0)) == (TabFrames*) -1)
        return -1;
    
    //Inicializamos a estrutura de tabela de frames
    for (int i = 0; i < NUMERO_FRAMES; i++) {
        (*tabFrames)->frames[i].num_pag = -1;
        (*tabFrames)->frames[i].tempo_ref = -1;
    }
    
    (*tabFrames)->frames_ocupados = 0;
    (*tabFrames)->num_exec_proc_subst = 0;
    
    return idshm;
}

//--------------------------------------------------------------------------------------------------
int removeTabFrames(int shmid, TabFrames* tabFrames){
    
    if (shmdt(tabFrames) < 0) return -1;
    
    return shmctl(shmid, IPC_RMID, 0);
}

//--------------------------------------------------------------------------------------------------
void imprimeTabFrames(TabFrames* tabFrames){
    TabFrames *tabFrames_aux;
    
    tabFrames_aux = tabFrames;

    printf("\nNumero de execucoes do processo de substituicao: %d", tabFrames_aux->num_exec_proc_subst);
    
    printf("\n\nConfiguracao final da memoria:");
    printf("\n.-------------------------------.");
    printf("\n|Pagina\t|Tempo de Referencia\t|");
    printf("\n.-------------------------------.");
    for(int i = 0; i < NUMERO_FRAMES; i++) {
        if (tabFrames_aux->frames[i].num_pag < 0)
            printf("\n|Livre\t|--\t\t\t|");
        
        else
            printf("\n|%d\t|%lu\t\t\t|", tabFrames_aux->frames[i].num_pag, tabFrames_aux->frames[i].tempo_ref);
    }
    
    printf("\n'-------------------------------'\n\n");
    
}