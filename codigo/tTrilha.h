/** Define um TAD representando uma pilha duplamente encadeada de unsigned char, representando um bit.
 * @file tTrilha.h
 * @author Conrado Antoniazi dos Santos (conradoantoniazi@gmail.com) e Raphael Correia Dornelas (dornelasrapha@gmail.com)
 */

#ifndef _TLISTADADOS_H_
#define _TLISTADADOS_H_

#include "tAb.h"

/// @brief uma pilha de caracteres
typedef struct Trilha tTrilha;

/// @brief aloca espaco na memoria para uma
/// variavel do tipo tTrilha
/// @return a trilha criada
/// @post um espaco de memoria do tamanho de 
/// tTrilha ocupado
tTrilha *CriaTrilha();

/// @brief libera a memoria usada por p
/// @param p uma trilha valida
/// @pre p devidamente alocada na memoria
/// @post o espaco ocoupado por p fica livre
void DesalocaTrilha(tTrilha *p);

/// @brief insere c no final de p
/// @param p uma trilha valida
/// @param c um caractere
/// @pre p devidamente alocada na memoria
/// @post c na ultima celula de p;
/// tamanho de p incrementado
void PushTrilha(tTrilha *p, unsigned char c);

/// @brief retira a ultima celula de p
/// @param p uma trilha valida
/// @return o char da ultima celula de p
/// @pre p devidamente alocada na memoria
/// @post p fica sem sua ultima celula e
/// tem seu tamanho decrementado
unsigned char PopTrilha(tTrilha *p);

/// @brief obtem o tamanho de p
/// @param p uma trilha valida
/// @return o tamanho de p
/// @pre p devidamente alocada na memoria
int getSizeTrilha(tTrilha *p);

/// @brief cria um vetor de char*
/// @return o vetor criado
/// @pre a constante TAM_ASCII precisa estar definida
/// @post um espaco do tamanho de TAM_ASCII.(char*) ocupado
unsigned char **CriaTabelaCodificacao();

/// @brief libera a memoria usada por table
/// @param table um vetor valido de char*
/// @post o espaco usado por table fica livre
void DesalocaTabelaCodificacao(unsigned char **table);

/// @brief constroi uma string com base nas
/// celulas de t
/// @param t uma trilha valida
/// @return uma string alocada dinamicamente
/// @pre t devidamente alocado na memoria
/// @post uma nova string ocupado um espaco
/// de memoria (tamnanho de t).char
unsigned char* getInfoTrilha(tTrilha *t);

/// @brief percorre ab preenchendo t, obtem os caracteres das folhas,
///  e entao coloca a trilha no indice correspondente de table
/// @param table uma tabela valida
/// @param t uma trilha valida
/// @param ab uma arvore binaria valida
/// @pre table, t e ab alocadas devidamente na memoria
/// @post n strings de tamanho t (t = numero de nos ate uma folha de ab)
/// alocadas na memoria e no indice correspondente de table, que e' 
/// o ascii do caracter encontrado
void PreencheTabelaCodificacao(unsigned char** table, tTrilha* t, tAb* ab);

#endif