/** Define um TAD representando uma lista duplamente encadeada de árvores binárias.
 * @file tLista.h
 * @author Conrado Antoniazi dos Santos (conradoantoniazi@gmail.com) e Raphael Correia Dornelas (dornelasrapha@gmail.com)
 */

#ifndef _TLISTA_H_
#define _TLISTA_H_

/// @brief uma lista duplamente encadedada com sentinela
typedef struct lista tLista;

#include "tAb.h"

/// @brief aloca uma estrutura tLista na memoria
/// @return a lista criada
tLista* CriaLista();

/// @brief libera a memoria usada por l
/// @param l um ponteito do tipo tLista
void DesalocaLista(tLista* l);

/// @brief insere ab em l de forma ordenada
/// @param l uma lista valida
/// @param ab uma arvore binaria valida
/// @pre l e ab devidamente alocadas na memoria
/// @post ab inserida ordenada em l, levando 
/// em conta o valor de sua frequencia, tamanho
/// de l incrementado
void InsereLista(tLista *l, tAb *ab);

/// @brief retira o primeiro item de l
/// @param l uma lista valida
/// @return a arvore da primeira celula de l
/// @pre l devidamente alocada na memoria
/// @post l menor, com seu primeiro item
/// modificado; tamanho de l decrementado
tAb* RetiraLista(tLista *l);

/// @brief obtem o tamanho de l
/// @param l uma lista valida
/// @return o tamanho de l
/// @pre l devidamente alocada na memoria
int getSizeLista(tLista *l);

/// @brief aloca memoria para uma lista e
/// a preenche com base em vet
/// @param vet vetor onde cada posicao representa
/// o indice ascii de um caracter, ao passo que seu
/// conteudo indica sua frequencia num texto
/// @return uma lista com n arvores, construidas a partir
/// dos n elementos de vet que sao diferentes de 0
tLista* CriaListaNos(int* vet);

#endif