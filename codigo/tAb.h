/** Define um TAD representando uma árvore binária de um caracter e sua frequência.
 * @file tAb.h
 * @author Conrado Antoniazi dos Santos (conradoantoniazi@gmail.com) e Raphael Correia Dornelas (dornelasrapha@gmail.com)
 */

#ifndef _tAb_H_
#define _tAb_H_

/// @brief Estrutura para uma arvore binaria
typedef struct ab tAb;

#include "bitmap.h"
#include "tLista.h"

/// @brief Verifica se uma arvore é folha
/// @param a 
/// @return Retorna 1 para folha e 0 para o contrário
int ehFolha(tAb *a);

/// @brief Cria dinamicamente uma 
/// estrutuara tAb
/// @param caractere o caracctere do no 
/// @param frequencia quantas vezes o caractere 
/// foi lido
/// @param sae a subarvore da esquerda
/// @param sad a subarvore da direita
/// @return um ponteiro valiod para a arvore criada
tAb *CriaAb(unsigned char caractere, unsigned int frequencia, tAb *sae, tAb *sad);

/// @brief Libera a memoria utilizada
/// por uma estrutura tAb
/// @param abb a arvore que se deseja desalocar
void DesalocaaAb(tAb *ab);

/// @brief Une duas arvores
/// @param a1 uma arvore valida
/// @param a2 outra arvore valida
/// @return uma nova arvore com no 
/// contendo a soma da frequencia em a1 e a2
tAb *JoinAb(tAb *a1, tAb*a2);

/// @brief Obtem a frequencia contida numa Ab
/// @param ab uma arvore valida
/// @return a frequencia contida em AB
unsigned int getFreqAb(tAb *ab);

/// @brief Obtem o caractere contido numa Ab
/// @param ab uma arvore valida
/// @return o caractere contido em Ab
unsigned char getChAb(tAb *ab);

/// @brief  Obtem o ponteiro para a subarvore da esquerda de uma arvore valida
/// @param ab 
/// @return Subarvore da esquerda
tAb* GetSae(tAb* ab);

/// @brief Obtem o ponteiro para a subarvore da direita de uma arvore valida
/// @param ab 
/// @return Subarvore da direita
tAb* GetSad(tAb* ab);

/// @brief Cria a arvore de codificacao de huffman
/// @param nos 
/// @return Retorna a arvore criada
tAb* CriaArvoreHuf(tLista* nos);

/// @brief carrega as informacoes de uma arvore 
/// binaria para um bitmap
/// @param ab uma arvore binaria valida
/// @param bm um bitmap valido
/// @pre ab e bm devidamente alocados na memoria;
/// deve haver espaco suficiente em bm para o dump de ab
/// @post as informacoes de ab estarao em bm caso
/// haja espaco para isso
void DumpArvoreBitmap(tAb *ab, bitmap *bm);

/// @brief constroi uma arvore binaria com base
/// no conteudo do bitmap
/// @param bm um bitmap valido
/// @param index um ponteiro de inteiro valido
/// @return uma arvore binaria construida com 
/// base no conteudo de bm
/// @pre bm estar devidamente alocado e index ser um 
/// indice valido no conteudo de bm
/// @post uma nova arvore alocada na memoria
tAb *ReadArvoreBitmap(bitmap *bm, unsigned int* index);

#endif