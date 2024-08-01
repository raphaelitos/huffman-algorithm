#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLista.h"
#include "tTrilha.h"
#include "utils.h"

void Compacta(char *nomeArquivo){
    if(!nomeArquivo)TratarStructNula("compacta", "char*");

    //Cabecalho do arquivo compactado
    char pathOut[strlen(nomeArquivo) + strlen(EXTENSAO) + 2];
    sprintf(pathOut, "%s%s", nomeArquivo, EXTENSAO);

    int *vet = IniciaVetAscII();
    ContaFreqCaracteres(vet, nomeArquivo);

    tLista *nos = CriaListaNos(vet);
    tAb *arvHuf = CriaArvoreHuf(nos);

    tTrilha *pilha = CriaTrilha();
    unsigned char **table = CriaTabelaCodificacao();
    PreencheTabelaCodificacao(table, pilha, arvHuf);
    

    //colocando a arvore no binario
    bitmap *bmComp = bitmapInit(UM_MEGA);
    DumpArvoreBitmap(arvHuf, bmComp);
    
    BinDumpBitmap(bmComp, pathOut, 1);
    bitmapLibera(bmComp);


    //Conteudo do arquivo compactado
    FILE *entrada = fopen(nomeArquivo, "rb");
    if(!entrada)TratarFalhaAlocacao("arqIn compacta");

    unsigned char byte;
    bmComp = bitmapInit(UM_MEGA);

    while(1){
        size_t bytesRead = fread(&byte, sizeof(unsigned char), 1, entrada);

        if(bytesRead != 1) break;

        unsigned char *code = table[(unsigned int)byte];
        int tamStr = strlen(code);
        int tamBm = bitmapGetLength(bmComp);
        int max = bitmapGetMaxSize(bmComp);
        int i = 0;

        if((tamBm + tamStr) > max){
            
            for(i = 0; i < (max - tamBm); i++){
                bitmapAppendLeastSignificantBit(bmComp, (code[i] - '0'));
            }

            BinDumpBitmap(bmComp, pathOut, 1);
            bitmapLibera(bmComp);
            bmComp = bitmapInit(UM_MEGA);
        }

        for(i; i < tamStr; i++){
            bitmapAppendLeastSignificantBit(bmComp, (code[i] - '0'));
        }
    }
    BinDumpBitmap(bmComp, pathOut, 1);
    
    bitmapLibera(bmComp);
    DesalocaTrilha(pilha);
    DesalocaTabelaCodificacao(table);
    DesalocaaAb(arvHuf);
    DesalocaLista(nos);
    free(vet);
    fclose(entrada);
}

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
            printf("%d %d\n", bit, index);
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

    char *inputPath = argv[1];
    
    Compacta(inputPath);
    /*
       Descompacta(inputPath);
    */
    return EXIT_SUCCESS;
}