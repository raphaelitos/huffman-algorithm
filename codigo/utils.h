#ifndef UTILS_H_
#define UTILS_H_

#include "bitmap.h"

#define TAM_ASCII 256
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

/**
 * Compara dois termos validos e diz se sao iguais.
*/
int EhMesmoTermo(char *str1, char*str2);

int *IniciaVetAscII();

void ContaFreqCaracteres(int *vet, char *path);

void PrintVetInt(int *vet, int tam);

/// @brief salva bm num arquivo binario  
/// @param bm um bitmap valido
/// @param nomeArquivo o nome do arquivo onde bm 
/// sera salvo
/// @pre o caminho ser valido e o bitmap estar
/// devidamente alocado na memoria
/// @post um arquivo .bin nomeado por nomeArquivo
void BinDumpBitmap(bitmap *bm, char *nomeArquivo);

/// @brief cria um bitmap a partir de um
/// arquivo binario
/// @param path o camiho para o arquivo
/// @return o bitmao criado
/// @pre o caminho levar a um arquivo binario valido
bitmap *BinReadBitmap(char *path);

#endif