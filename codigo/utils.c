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
        vet[(int)byte]++;
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

void BinDumpBitmap(bitmap *bm, char *nomeArquivo, int writeTam){
	if(!bm || !nomeArquivo) TratarStructNula("BinDump", "bitmap ou path");
	char dest[strlen(nomeArquivo) + 6];

	FILE *arq = fopen(nomeArquivo, "ab");
	if(!arq)TratarFalhaAlocacao("arquivo do bitmap dump");
	
	unsigned int tam = bitmapGetLength(bm);
	unsigned int qtdBytes = tam / 8;
	unsigned int restoBits = tam % 8;
    
    if(writeTam) {
	    unsigned char c = 's';
        if(tam == bitmapGetMaxSize(bm)){
            c = 'n';
        }
        fwrite(&c, sizeof(unsigned char), 1, arq);
        
        if(tam != bitmapGetMaxSize(bm)){
            fwrite(&tam, sizeof(unsigned int), 1, arq);
        }
    }
	
    //for(int i = 0; i < qtdBytes; i++) printf("%u ", bitmapGetContents(bm)[i]);
	fwrite(bitmapGetContents(bm), sizeof(unsigned char), qtdBytes, arq);
	if(restoBits){
		unsigned char byte = (unsigned char)0;
		
		for(unsigned int b = 0; b < restoBits; b++){
			byte |= bitmapGetBit(bm, ((qtdBytes * 8) + b)) << (7 - b);
		}
		
		//byte preenchido com os n bits do ultimo byte
		//do bitmap, caso esse byte nao esteja cheio
        //printf("%u\n", byte);
		fwrite(&byte, sizeof(unsigned char), 1, arq);
	}
	
	fclose(arq);
}

bitmap *BinReadBitmap(FILE *arq) {
    if (!arq) {
        TratarStructNula("BinRead", "arquivo");
        return NULL;
    }

    unsigned char c;
    unsigned int tam;
    size_t bytesRd = fread(&c, sizeof(unsigned char), 1, arq);

	if(bytesRd != 1){
        printf("fim do arquivo onde o bitmap estava\n");
        return NULL;
    }
    if(c == 'n'){
        tam = UM_MEGA;
    }
    else{
        fread(&tam, sizeof(unsigned int), 1, arq);
    }
    
    unsigned int qtdBytes = tam / 8;
    unsigned int restoBits = tam % 8;

    unsigned char *contents = (unsigned char *)calloc((qtdBytes + (restoBits ? 1 : 0)), sizeof(unsigned char));
    if(!contents) {
        fclose(arq);
        TratarFalhaAlocacao("contents para bitmap");
        return NULL;
    }

    fread(contents, sizeof(unsigned char), qtdBytes + (restoBits ? 1 : 0), arq);

    bitmap *bm = bitmapInit(tam);
    if(!bm) {
        free(contents);
        TratarFalhaAlocacao("bitmap em readBin");
        return NULL;
    }
    printf("qtdBytes: %d\n", qtdBytes);
    for(unsigned int i = 0; i < qtdBytes; i++) {
        bitmapAppendByte(bm, contents[i]);
    }

    if(restoBits) {
        printf("entrando no byte quebrado\n");
        unsigned char byte = contents[qtdBytes];
        for(unsigned int b = 0; b < restoBits; b++) {
            unsigned char bit = (byte >> (7 - b)) & 0x01;
            bitmapAppendLeastSignificantBit(bm, bit);
        }
    }

    free(contents);
    return bm;
}