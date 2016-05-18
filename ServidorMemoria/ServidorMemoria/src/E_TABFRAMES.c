//#################################################################################################
/*! \file M_ALOCPAG.c
 *
 *  \brief Modulo de estrutura de tabela de frames
 *
 *  Modulo responsavel por implementar os metodos relacionados as tabelas de frames
 */
//##################################################################################################

#include "../include/E_TABFRAMES.h"

#define M_TABFRAMES


//--------------------------------------------------------------------------------------------------
int inicializaTabFrames(int chave, TabFrames* tabFrames){
    
    int idshm;
    
    //Criamos a area de memoria compartilhada para armazenar a tabela
    if ((idshm = shmget(chave, sizeof(TabFrames), IPC_CREAT | 0x1FF) < 0))
        return -1;
    
    //Mapeamos a estrutura na memoria
    if((tabFrames = (TabFrames*) shmat(idshm, (char*) 0, 0)) == (TabFrames*) -1)
        return -1;
    
    //Inicializamos a estrutura de tabela de frames
    for (int i = 0; i < NUMERO_FRAMES; i++) {
        tabFrames->frames[i].num_pag = -1;
        tabFrames->frames[i].tempo_ref = -1;
    }
    
    tabFrames->frames_ocupados = 0;
    
    return idshm;
}

//--------------------------------------------------------------------------------------------------
int removeTabFrames(int shmid, TabFrames* tabFrames){
    
    if (shmdt(tabFrames) < 0) return -1;
    
    return shmctl(shmid, IPC_RMID, 0);
}