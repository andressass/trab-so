//#################################################################################################
/*! \file M_PROCUSUARIO.c
 *
 *  \brief Modulo do processo de usuario.
 *
 *  Modulo responsavel por implementar os metodos relacionados a criacao de N processos de usuarios, em que cada um realiza uma chamada a primitiva referencia_pagina(i), onde i eh o numero da pagina. Essas paginas a serem referenciadas por um processo n estao no arquivo pag_processo_n.
 */
//##################################################################################################


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "../include/E_MENSAGEM.h"


//--------------------------------------------------------------------------------------------------
// Definicoes
//--------------------------------------------------------------------------------------------------
#define NPROC 10 //!< Numero total de processos de usuario


//--------------------------------------------------------------------------------------------------
// Variaveis Globais
int pid; //!< id do processo atual

int msg_aloc_id; //!< id das filas de mensagem de entrada do alocador
int msg_usu_id; //!< id das filas de mensagem de notificacao dos usuarios


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo inicial do sistema
 *
 */
int main(int argc, const char * argv[])
{
    char nomeArquivo[19];
    FILE* fp;
    int pag_ref_char, pag_ref_int;
    
    if(argc != 2) {
        printf("Você esqueceu de colocar o numero do processo!!!\n\n");
        exit(1);
    }

    strcat(nomeArquivo, "pag_processo_");
    
    //Concatena o numero do processo ao nome incompleto do arquivo
    strcat(nomeArquivo, argv[1]);
    
    //Concate a extensao ao arquivo
    strcat(nomeArquivo, ".txt");
    
    //Abre o arquivo para a leitura das paginas a serem referenciadas
    fp = fopen(nomeArquivo, "r");
    
    if(fp == NULL) {
        printf("O arquivo %s nao pode ser aberto.\n\n", nomeArquivo);
        exit(2);
    }
    
    //Obtencao das filas de mensagens dos processos de alocacao e substituicao de paginas
    msg_aloc_id = msgget(KEY_T0, 0x1FF);
    msg_usu_id = msgget(KEY_T1, 0x1FF);
    
    Mensagem* m1 = inicializaMensagem();
    
    //Verificamos se houve erro na criacao das filas de mensagens
    if (msg_usu_id < 0 || msg_aloc_id < 0) {
        printf("Erro na obtencao das filas de mensagem. Encerrando servidor...\n");
        exit(1);
    }
    
    pag_ref_char = getc(fp);
    while(pag_ref_char != EOF) {
        if (pag_ref_char != ',' && pag_ref_char != '\n') {
            pag_ref_int = pag_ref_char - '0';
            //Referencia pagina
            printf("%d", pag_ref_int);
            m1->pid = getpid();
            m1->num = pag_ref_int;
            if(msgsnd(msg_aloc_id, m1, sizeof(Mensagem), 0) < 0)
                printf("Erro de envio mensagem\n\n");
            
            if(msgrcv(msg_usu_id, m1, sizeof(Mensagem), getpid(), 0) < 0)
                printf("Erro de recebimento de mensagem\n\n");
            else printf("\n\nUSUARIO: Recebi mensagem!!\n\n");
        }
        pag_ref_char = getc(fp);
    }
    
    fclose(fp);
    
    return 0;
    
}
