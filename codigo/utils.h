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
void ContaFreqCaracteres(int *vet, char *path);

/// @brief imprime um vetor de inteiros
/// @param vet um vetor valido
/// @param tam o tamanho do vetor
void PrintVetInt(int *vet, int tam);

/// @brief salva bm num arquivo binario  
/// @param bm um bitmap valido
/// @param arq o  arquivo onde bm 
/// sera salvo
/// @param writeTam flag que indica a função se deve
/// ou nao escrever o tamanho do bitmap
/// 1 para habilitar a escrita e 0 para o contrário
/// @pre o caminho ser valido e o bitmap estar
/// devidamente alocado na memoria
/// @post um arquivo .bin nomeado por nomeArquivo
void BinDumpBitmap(bitmap *bm, FILE *arq);

/// @brief cria um bitmap a partir de um
/// arquivo aberto em modo de leitura em binario
/// @param arq o arquivo que sera lido
/// @return o bitmap criado ou null se essa
/// criacao nao for concretizada
/// @pre arq deve ser um arquivo valido 
/// aberto de forma correta
/// @post um bitmap criado com no ate 1Mb 
/// de dados do arquivo
bitmap *BinReadBitmap(FILE *arq);

#endif