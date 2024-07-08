#ifndef __TFILA_H__
#define __TFILA_H__

#include "amostra.h"

typedef struct fila tFila;

/// @brief Cria dinamicamente uma fila
/// @return a lista vazia criada
tFila *criaFila();

/// @brief Desaloca o espaco utilizado por uma fila 
/// @param f uma fila valida
void desalocaFila(tFila *f);

/// @brief Insere um elemento no final da fila 
/// @param f uma fila valida
/// @param a uma amostra valida
void insereFila(tFila *f, Amostra *a);

/// @brief Retira um elemento (do inicio) da fila
/// @param f uma fila valida
/// @return A amostra do elemento retirado
Amostra *retiraFila(tFila *f);

/// @brief Imprime os elementos de uma fila na ordem em que
/// foram inseridos
/// @param f uma fila valida
void imprimeFila(tFila *f);

/// @brief Processa todas as amostras de uma fila
/// @param naoProcessadas as amostras que precisam de testagem
/// @param negativas destino das amostras identificadas negativas
/// @param positivas destino das amostras identificadas positivas
void processaAmostrasFila(tFila *naoProcessadas, tFila *negativas, tFila *positivas);

/// @brief Obtem o tamanho de uma fila
/// @param f uma fila valida
/// @return o tamanho da fila
int getTamanhoFila(tFila *f);

#endif