//#################################################################################################
/*! \file I_SEMAFORO.h
 *
 *  \brief Interface dos semaforos de Dijkstra
 *
 *  Interface responsavel por disponibilizar servicos responsaveis pela manipulacao dos semaforos de Dijkstra.
 */
//##################################################################################################

#ifndef SEMAFORO_h
#define SEMAFORO_h

#ifdef M_SEMAFORO
#define EXT5
#else
#define EXT5 extern
#endif


#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

//--------------------------------------------------------------------------------------------------
// Metodos
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por criar um conjunto de sem_num semaforos com a chave e os valores iniciais
 * passados como paramtero. As permissoes de acesso sao todas setadas.
 *
 * \param chave Chave para a criacao do conjunto de semaforos
 * \param nsems Numero de semaforos no conjunto
 * \param valor_inicial Valor inicial de cada um dos semaforos do conjunto
 * \return id semaforo, em caso de sucesso. -1, em caso de erro
 */
EXT5 int inicializaSemaforo(int chave, int nsems, int valor_inicial);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por remover um conjunto de semaforos
 *
 * \param semid id do conjunto de semaforos
 * \return O, em caso de sucesso. -1, em caso de erro
 */
EXT5 int removeSemaforo(int semid);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar a primitiva P() de Dijkstra. Quando o valor do semaforo for maior ou igual a 1, o valor dele eh decrementado. Caso contrario, bloqueia o processo.
 *
 * \param semid id do conjunto de semaforos
 * \param sem_num numero do semaforo
 * \return 0, em caso de sucesso, -1, em caso de erro
 */
EXT5 int P(int semid, int sem_num);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar a primitiva V() de Dijkstra. O valor do semaforo eh incrementado.
 *
 * \param semid id do conjunto de semaforos
 * \param sem_num numero do semaforo
 * \return 0, em caso de sucesso, -1, em caso de erro
 */
EXT5 int V(int semid, int sem_num);

#endif /* SEMAFORO_h */
