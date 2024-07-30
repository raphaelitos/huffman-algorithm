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

int *IniciaVetAscII(){
    int *vet = (int*)calloc(TAM_ASCII, sizeof(int));
    if(!vet) exit(EXIT_FAILURE);
    return vet;
}

void ContaFreqCaracteres(int *vet, char *path){
    FILE *arq = fopen(path, "rb");
    if(!arq) exit(EXIT_FAILURE);
    
    unsigned char byte;
    while (fread(&byte, sizeof(unsigned char), 1, arq) == 1) {
        vet[byte]++;
    }

    fclose(arq);
}

void PrintVetInt(int *vet, int tam){
    if(!vet) return;
    printf("[ ");
    for(int i = 0; i < tam; i++){
        if(vet[i]){
            printf("%c ", (unsigned char)i);
        }
    }
    printf("]\n");
}
/*
void BinDumpBitmap(bitmap *bm, char *path, char *nomeArquivo){
	if(!bm || !path || !nomeArquivo) TratarStructNula("BinDump", "bitmap ou path");
	char dest[strlen(path) + strlen(nomeArquivo) + 6];
	sprintf(dest, "%s/%s.bin", path, nomeArquivo);// esse .bin aqui ta suspeito

	FILE *arq = fopen(dest, "ab");
	if(!arq)TratarFalhaAlocacao("arquivo do bitmap dump");
	
	unsigned int tam = bitmapGetLength(bm);
	unsigned int qtdBytes = tam / 8;
	unsigned int restoBits = tam % 8;
	unsigned char byte;

	fwrite(&tam, sizeof(unsigned int), 1, arq);
	for(int i = 0; i < qtdBytes ; i++){
		byte = bitmapGetByte(bm, i * 8);
		fwrite(&byte, sizeof(unsigned char), 1, arq);
	}
	if(restoBits){
		byte = (unsigned char)0;
		for(int b = 0; b < restoBits; b++){
			byte |= bitmapGetBit(bm, ((qtdBytes * 8) + b)) << (7 - b);
		}
		//byte preenchido com os n bits do ultimo byte
		//do bitmap, caso esse byte nao esteja cheio
		fwrite(&byte, sizeof(unsigned char), 1, arq);
	}
	
	fclose(arq);
}
*/

void BinDumpBitmap(bitmap *bm, char *nomeArquivo){
	if(!bm || !nomeArquivo) TratarStructNula("BinDump", "bitmap ou path");
	char dest[strlen(nomeArquivo) + 6];
	//sprintf(dest, "./%s.bin", nomeArquivo);// esse .bin aqui ta suspeito

	FILE *arq = fopen(nomeArquivo, "ab");
	if(!arq)TratarFalhaAlocacao("arquivo do bitmap dump");
	
	unsigned int tam = bitmapGetLength(bm);
	unsigned int qtdBytes = tam / 8;
	unsigned int restoBits = tam % 8;
	unsigned char c = 's';
	if(tam == bitmapGetMaxSize(bm)) c = 'n';
	
	fwrite(&c, sizeof(unsigned char), 1, arq);
	
	if(tam != bitmapGetMaxSize(bm)) fwrite(&tam, sizeof(unsigned int), 1, arq);
	
	fwrite(bitmapGetContents(bm), sizeof(unsigned char), qtdBytes, arq);
	if(restoBits){
		unsigned char byte = (unsigned char)0;
		
		for(int b = 0; b < restoBits; b++){
			byte |= bitmapGetBit(bm, ((qtdBytes * 8) + b)) << (7 - b);
		}
		
		//byte preenchido com os n bits do ultimo byte
		//do bitmap, caso esse byte nao esteja cheio
		fwrite(&byte, sizeof(unsigned char), 1, arq);
	}
	
	fclose(arq);
}

/*
bitmap *BinReadBitmap(char *path){
	if(!path) TratarStructNula("BinRead", "bitmap ou path");

	FILE *arq = fopen(path, "rb");
	if(!arq)TratarFalhaAlocacao("arquivo do bitmap dump");
	
	unsigned int tam;
	fread(&tam, sizeof(unsigned int), 1, arq);

	unsigned int qtdBytes = tam / 8;
	unsigned int restoBits = tam % 8;
	unsigned char byte;

	bitmap *bm = bitmapInit(tam);

	for(int i = 0; i < qtdBytes; i++){
		fread(&byte, sizeof(unsigned char), 1, arq);
		bitmapAppendByte(bm, byte);
	}
	if(restoBits){
		fread(&byte, sizeof(unsigned char), 1, arq);
		unsigned char bit;
		for(int b = 0; b < restoBits; b++){
			bit = (byte >> (7 - b)) & 0x01;
			//se tam nao representar um valor inteiro de bytes,
			//os n (tam % 8) bits mais significativos de byte sao
			//colocados no bitmap
			
			bitmapAppendLeastSignificantBit(bm ,bit);
		}
	}
	
	fclose(arq);
	return bm;
}
*/

/*bitmap *BinReadBitmap(char *path) {
    if (!path) {
        TratarStructNula("BinRead", "bitmap ou path");
        return NULL;
    }

    FILE *arq = fopen(path, "rb");
    if (!arq) {
        TratarFalhaAlocacao("arquivo do bitmap dump");
        return NULL;
    }

	unsigned char c;
    unsigned int tam;
	fread(&c, sizeof(unsigned char), 1, arq);

	if(c == 'n') tam = 1024;
    else fread(&tam, sizeof(unsigned int), 1, arq);

    unsigned int qtdBytes = tam / 8;
	unsigned int restoBits = tam % 8;
	int resto = 0;
	if(restoBits) resto++;

    unsigned char *contents = (unsigned char *)malloc(qtdBytes + resto);
    if(!contents) {
        fclose(arq);
        TratarFalhaAlocacao("alocação da memória para o bitmap");
        return NULL;
    }

    fread(contents, sizeof(unsigned char), qtdBytes + resto, arq);

    bitmap *bm = bitmapInit(tam);
    if(!bm) {
        free(contents);
        TratarFalhaAlocacao("bitmap em readBin");
        return NULL;
    }

    for(int i = 0; i < qtdBytes; i++) {
        bitmapAppendByte(bm, contents[i]);
    }

	if(restoBits) {
        unsigned char byte = contents[qtdBytes + resto]; <- erro aqui
        for(unsigned int b = 0; b < restoBits; b++) {
            unsigned char bit = (byte >> (7 - b)) & 0x01;
            bitmapAppendLeastSignificantBit(bm, bit);
        }
    }

    fclose(arq);
    free(contents);
    return bm;
}*/

bitmap *BinReadBitmap(char *path) {
    if (!path) {
        TratarStructNula("BinRead", "bitmap ou path");
        return NULL;
    }

    FILE *arq = fopen(path, "rb");
    if (!arq) {
        TratarFalhaAlocacao("arquivo do bitmap dump");
        return NULL;
    }

    unsigned char c;
    unsigned int tam;
    fread(&c, sizeof(unsigned char), 1, arq);

    if(c == 'n') tam = 1024;
    else fread(&tam, sizeof(unsigned int), 1, arq);

    unsigned int qtdBytes = tam / 8;
    unsigned int restoBits = tam % 8;

    unsigned char *contents = (unsigned char *)malloc(qtdBytes + (restoBits ? 1 : 0));
    if(!contents) {
        fclose(arq);
        TratarFalhaAlocacao("alocação da memória para o bitmap");
        return NULL;
    }

    fread(contents, sizeof(unsigned char), qtdBytes + (restoBits ? 1 : 0), arq);

    bitmap *bm = bitmapInit(tam);
    if(!bm) {
        free(contents);
        TratarFalhaAlocacao("bitmap em readBin");
        return NULL;
    }

    for(int i = 0; i < qtdBytes; i++) {
        bitmapAppendByte(bm, contents[i]);
    }

    if(restoBits) {
        unsigned char byte = contents[qtdBytes];
        for(unsigned int b = 0; b < restoBits; b++) {
            unsigned char bit = (byte >> (7 - b)) & 0x01;
            bitmapAppendLeastSignificantBit(bm, bit);
        }
    }

    fclose(arq);
    free(contents);
    return bm;
}
