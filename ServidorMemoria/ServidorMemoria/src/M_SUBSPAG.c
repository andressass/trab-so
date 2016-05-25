//#################################################################################################
/*! \file M_SUBSPAG.c
 *
 *  \brief Modulo do substituidor de paginas
 *
 *  Modulo responsavel por implementar os servicos responsaveis pela substituicao de paginas
 *  do servidor de memoria.
 */
//##################################################################################################

#include "../include/I_SUBSPAG.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <stdio.h>

#define M_SUBSPAG


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por encerrar o substituidor de paginas
 */
void encerraSubstituidor()
{
    exit(0);
}



//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por implementar os servicos relativos a liberacao da pagina com o tempo de
 * referencia mais antigo da tabela de frames.
 *
 * \param tab_frames Tabela de frames
 */
void liberaPaginaMaisAntiga(TabFrames* tab_frames){
    
    int older_frame = 0; //Indice do frame mais antigo (comeca no primeiro)
    double older_time = tab_frames->frames[0].tempo_ref;
    
    //Escolhemos a pagina que foi referenciada a mais tempo
    for (int i = 1; i < NUMERO_FRAMES; i++){
        //Se o tempo de referencia for mais antigo que o mais antigo ja obtido e o frame estiver ocupado
        if(tab_frames->frames[i].num_pag >= 0 && tab_frames->frames[i].tempo_ref < older_time){
           
            //Atualizamos o indice do frame mais antigo
            older_frame = i;
            
            //Atualizamos o tempo mais antigo
            older_time = tab_frames->frames[i].tempo_ref;
        }
    }

    //Liberamos a pagina mais antiga e atualizams o numero de frames livres
    printf("\n\nSUBSTITUIDOR: Substituindo pagina %d.\n", tab_frames->frames[older_frame].num_pag);
    tab_frames->frames[older_frame].num_pag = -1;
    tab_frames->frames[older_frame].tempo_ref = -1;
    tab_frames->frames_ocupados--;
}


//--------------------------------------------------------------------------------------------------
int servicoSubstuicaoPaginas(TabFrames* tab_frames, int semid){
    signal(SIGUSR1, encerraSubstituidor);
    
    while (1) {
        
        P(semid, SOLIC_LIB_PAG); //Espera solicitacao de substituicao de paginas
        P(semid, MUTEX); //Entra da secao critica
        
        printf("\n\nSUBSTITUIDOR: Substituindo paginas!\n");
        //Executa o servico de substituicao de pagina
        while(tab_frames->frames_ocupados >= OCUPACAO_OK)
            liberaPaginaMaisAntiga(tab_frames);
        
        V(semid, RESP_LIB_PAG); //Notifica resultado ao alocador
        V(semid, MUTEX); //Sai da secao critica
        
        
    }
}