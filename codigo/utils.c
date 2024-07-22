#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void TratarStructNula(const char *nomeFuncao, const char *nomeStruct){
	printf("%s nula na funcao %s!\n", nomeStruct, nomeFuncao);
	exit(EXIT_FAILURE);
}

void TratarFalhaAlocacao(const char *nomeStruct){
	printf("Falha na criacao de %s\n", nomeStruct);
	exit(EXIT_FAILURE);
}

int EhMesmoTermo(char *str1, char*str2){
	if(!str1 || !str2) TratarStructNula("ehmesmotermo", "char*");
	return !strcmp(str1, str2);
}

void BinDumpBitmap(bitmap *bm, char *path, char *nomeArquivo){
	if(!bm || !path || !nomeArquivo) TratarStructNula("BinDump", "bitmap ou path");
	char dest[strlen(path) + strlen(nomeArquivo) + 6];
	sprintf(dest, "%s/%s.bin", path, nomeArquivo);

	FILE *arq = fopen(dest, "wb");
	if(!arq)TratarFalhaAlocacao("arquivo do bitmap dump");
	
	unsigned int tam = bitmapGetLength(bm);

	if(tam % 8){
	/*
		printf("tamanho do bitmap nao esta redondo. Encerrando...\n");
		exit(EXIT_FAILURE);
	*/
		for(int b = 0; b < (8 - (tam % 8)); b++){
			bitmapAppendLeastSignificantBit(bm, 0);
		}
	}
	tam = bitmapGetLength(bm);
	unsigned char byte;
	fwrite(&tam, sizeof(unsigned int), 1, arq);
	for(int i = 0; (i * 8) < tam; i++){
		byte = bitmapGetByte(bm, i * 8);
		fwrite(&byte, sizeof(unsigned char), 1, arq);
	}
	
	fclose(arq);
}

bitmap *BinReadBitmap(char *path){
	if(!path) TratarStructNula("BinRead", "bitmap ou path");

	FILE *arq = fopen(path, "rb");
	if(!arq)TratarFalhaAlocacao("arquivo do bitmap dump");
	
	unsigned int tam = 0;
	fread(&tam, sizeof(unsigned int), 1, arq);

	bitmap *bm = bitmapInit(tam);

	unsigned char byte;
	for(int i = 0; i < (tam/8); i++){
		fread(&byte, sizeof(unsigned char), 1, arq);
		bitmapAppendByte(bm, byte);
	}
	
	fclose(arq);
	return bm;
}