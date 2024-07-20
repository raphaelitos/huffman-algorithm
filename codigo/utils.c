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
	char dest[strlen(path) + strlen(nomeArquivo) + 5];
	sprintf(dest, "%s/%s.bin", path, nomeArquivo);

	FILE *arq = fopen(dest, "wb");
	if(!arq)TratarFalhaAlocacao("arquivo do bitmap dump");
	if(bitmapGetLength(bm) % 8){
		printf("tamanho do bitmap nao esta redondo. Encerrando...\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < (bitmapGetLength(bm)/8); i++){
		fwrite(bitmapGetByte(bm, i), sizeof(unsigned char), 1,arq);
	}
	fclose(arq);
}