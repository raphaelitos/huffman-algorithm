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

    if (tamIn <= tamExt || strcmp((nomeArquivoIn + tamIn - tamExt), EXTENSAO)) {
        printf("ERRO: O arquivo deve ter a extensao .comp\n");
        return;
    }

    size_t tamCpy = tamIn - tamExt;
    char pathOut[tamCpy + 1];
    strncpy(pathOut, nomeArquivoIn, tamCpy);
    pathOut[tamCpy] = '\0';

    FILE *arqIn = fopen(nomeArquivoIn, "rb");
    if(!arqIn) TratarFalhaAlocacao("arqIn em descompacta");

    //reconstruindo arvore
    bitmap* bm = BinReadBitmap(arqIn);

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

        bitmap* bmDescomp = bitmapInit(UM_MEGA);

        while(index < bitmapGetLength(bm)) {
            bit = (int)bitmapGetBit(bm, index);
            index++;
            if(bit == 0) aux = GetSae(aux);
            else aux = GetSad(aux);

            if(bitmapGetLength(bmDescomp) >= bitmapGetMaxSize(bmDescomp)) {
                BinDumpBitmap(bmDescomp, pathOut, 0);
                bitmapLibera(bmDescomp);
                bmDescomp = bitmapInit(UM_MEGA);
            }
            if(ehFolha(aux)) {
                bitmapAppendByte(bmDescomp, getChAb(aux));
                aux = arvHuf; //reset da árvore para o próximo caractere
            }
        }

        //Salva o ultimo bitmap descompactado se ele nao tiver enchido
        if (bitmapGetLength(bmDescomp) > 0) {
            BinDumpBitmap(bmDescomp, pathOut, 0);
        }
        
        bitmapLibera(bmDescomp);
        bitmapLibera(bm);
    }
    
    DesalocaaAb(arvHuf);
    fclose(arqIn);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Caminho para o arquivo não informado. Encerrando o programa.\n");
        return EXIT_FAILURE;
    }
        
    Descompacta(argv[1]);
    
    return EXIT_SUCCESS;
}