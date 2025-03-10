/** Define umUm TAD pensado para suprir demandas mais gerais do projeto.
 * @file utils.h
 * @author Conrado Antoniazi dos Santos (conradoantoniazi@gmail.com) e Raphael Correia Dornelas (dornelasrapha@gmail.com)
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "bitmap.h"

#define TAM_ASCII 256
#define UM_MEGA 1048576

#define ESQUERDA '0'
#define DIREITA '1'

#define EXTENSAO ".comp"


/**
 * Encerra o programa apos avisar a funcao onde isso
 * ocorreu e de qual estrutura se trata
*/
void TratarStructNula(const char *nomeFuncao, const char *nomeStruct);

/**
 * Encerra o programa apos indicar o tipo 
 * de dado que iria ser alocado
*/
void TratarFalhaAlocacao(const char *nomeStruct);

/// @brief Inicializa um vetor de inteiros cujo tamanho depende
/// da constante TAM_ASCII no header
/// @return o vetor de inteiros inicializado
/// @pre a constante TAM_ASCII deve existir
int *IniciaVetAscII();

/// @brief conta a frequencia dos caracteres 
/// presente no arquivo encontrado em path
/// e salva no vetor
/// @param vet um vetor de inteiros 
/// @param path o caminho para o arquivo
/// @pre vet estar devidamente alocado 
/// e ter tamanho suficiente para 
/// representar o codigo ascii dos caracteres;
/// path ser um caminho valido de arquivo
/// @post o conteudo de vet modificado de acordo
/// com as frequencias contabilizadas
void ContaFreqCaracteres(int *vet, char *path);

/// @brief salva bm em arq 
/// @param bm um bitmap valido
/// @param arq um arquivo valido
/// @pre bm devidamente alocado na memoria e 
/// arq um arquivo aberto em modo "wb"
/// @post o conteudo de bm sera escrito em arq
void BinDumpBitmap(bitmap *bm, FILE *arq);

/// @brief cria um bitmap a partir de um
/// arquivo aberto em modo de leitura em binario
/// @param arq o arquivo que sera lido
/// @return o bitmap criado ou null se essa
/// criacao nao for concretizada
/// @pre arq deve ser um arquivo valido 
/// aberto em modo "rb"
/// @post um bitmap criado com no ate 1Mb 
/// de dados do arquivo
bitmap *BinReadBitmap(FILE *arq);

#endif