#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tAb.h"
#include "utils.h"

void Descompacta(char* nomeArquivoIn) {
    if(!nomeArquivoIn)TratarStructNula("Descompacta", "char*");

    //Tratando nome do arquivo
    size_t tamIn = strlen(nomeArquivoIn);
    size_t tamExt = strlen(EXTENSAO);
    size_t tamCpy = tamIn - tamExt;

    if (tamIn <= tamExt || strcmp((nomeArquivoIn + tamCpy), EXTENSAO)) {
        printf("ERRO: O arquivo deve ter a extensao .comp\n");
        return;
    }

    char pathOut[tamCpy + 1];
    strncpy(pathOut, nomeArquivoIn, tamCpy);
    pathOut[tamCpy] = '\0';

    FILE *arqIn = fopen(nomeArquivoIn, "rb");
    if(!arqIn) TratarFalhaAlocacao("arqIn em descompacta");

    FILE *arqOut = fopen(pathOut, "wb");
    if(!arqOut) TratarFalhaAlocacao("arqOut em descompacta");

    //reconstruindo arvore
    bitmap* bm = BinReadBitmap(arqIn);

    if(!bm){//arquivo vazio
        fclose(arqIn);
        fclose(arqOut);
        return;
    }

    unsigned int index = 0;
    tAb* arvHuf = ReadArvoreBitmap(bm, &index);
    tAb* aux = arvHuf;
    bitmapLibera(bm);

    //reconstruindo arquivo
    while(1){
        bm = BinReadBitmap(arqIn);
        
        if(bm == NULL) break;

        int bit = 0;
        unsigned int index = 0;

        while(index < bitmapGetLength(bm)) {
            bit = (int)bitmapGetBit(bm, index);
            index++;
            if(bit == 0) aux = GetSae(aux);
            else aux = GetSad(aux);

            if(ehFolha(aux)) {
                unsigned char c = getChAb(aux);
                fwrite(&c, sizeof(unsigned char), 1, arqOut);
                aux = arvHuf; //reset da árvore para o próximo caractere
            }
        }
        
        bitmapLibera(bm);
    }
    //fim da reconstrucao, liberacao de tudo
    DesalocaaAb(arvHuf);
    fclose(arqIn);
    fclose(arqOut);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Caminho para o arquivo não informado. Encerrando o programa.\n");
        return EXIT_FAILURE;
    }
        
    Descompacta(argv[1]);
    
    return EXIT_SUCCESS;
}