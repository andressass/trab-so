//#################################################################################################
/*! \file M_SEMAFORO.c
 *
 *  \brief Modulo dos semaforos de Dijkstra
 *
 *  Modulo responsavel por implementar as primitivas que atuam sobre os semaforos
 */
//##################################################################################################

#include "../include/E_SEMAFORO.h"

#define M_SEMAFORO

//--------------------------------------------------------------------------------------------------
int inicializaConjSemaforo(int chave, int nsems, int valor_inicial){
    
    int semid;
    
    //Estrutura de um semaforo
    union semaforoUnitario {
        int valor ;
        struct semid_ds *buffer ;
        ushort array[1] ;
    } semaforoUnitario;
    semaforoUnitario.valor = valor_inicial; //Definimos o valor inicial dos semaforos
    
    //Criamos o conjunto de semaforos
    if ((semid = semget(chave, nsems, IPC_CREAT | 0X1FF)) < 0)
        return -1;
    
    //Setamos o valor de cada um dos semaforos do conjunto
    for (int i = 0; i < nsems; i++)
        if(semctl(semid, i, SETVAL, semaforoUnitario) < 0) return -1;
    
    return semid;
}


//--------------------------------------------------------------------------------------------------
int removeConjSemaforo(int semid){
    return semctl(semid,0,IPC_RMID,0);
}


//--------------------------------------------------------------------------------------------------
int P(int semid, int sem_num)
{
    
    struct sembuf operacao[1];
    operacao[0].sem_num = sem_num ;
    operacao[0].sem_op = -1 ;
    operacao[0].sem_flg = SEM_UNDO ;
    
    return (semop(semid, operacao, 1));
}


//--------------------------------------------------------------------------------------------------
int V(int semid, int sem_num)
{
    struct sembuf operacao[1];
    operacao[0].sem_num = sem_num ;
    operacao[0].sem_op =  1 ;
    operacao[0].sem_flg = SEM_UNDO ;
    
    return semop(semid, operacao, 1);
}
