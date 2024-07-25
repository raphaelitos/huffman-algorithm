#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLista.h"
#include "tTrilha.h"
#include "utils.h"

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

void Descompacta(bitmap* bm, int inic, FILE* arvBin, tAb* arvHuf) {
    tAb* aux = arvHuf;
    int bit = 0;
    bitmap* bmDescomp = bitmapInit(bitmapGetMaxSize(bm));    

    while(inic <= bitmapGetLength(bm)) {
        if(bitmapGetLength(bmDescomp) >= bitmapGetMaxSize(bmDescomp)) {
            //BinDumpBitmap(bmDescomp, ...);
            //SetLengthBitmap(bmDescomp, 0);
        }
        if(ehFolha(aux)) {
            bitmapAppendByte(bmDescomp, getChAb(aux));
        }

        bit = bitmapGetBit(bm, inic);
        inic++;
        if(bit == 0) aux = GetSae(aux);
        else aux = GetSad(aux);
    }
}

int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("Caminho para arquivos não informado. Encerrando programa.\n");
        exit(EXIT_FAILURE);
    }

    int* vet = IniciaVetAscII();
    char path[1000];
    sprintf(path, "%s/input/text.txt", argv[1]);

    ContaFreqCaracteres(vet, path);
    PrintVetInt(vet, TAM_ASCII);

    tLista *nos = CriaListaNos(vet);
    tAb *arvHuf = CriaArvoreHuf(nos);

    tTrilha* pilha = CriaTrilha();
    unsigned char** table = CriaTabelaCodificacao();
    PreencheTabelaCodificacao(table, pilha, arvHuf);
    ImprimeTabela(table);

    printf("ARV ORIGINAL +++++++++++++++++++++++++++++++++++++++++++++\n");
    ImprimeArvore(arvHuf, -1);
    
    bitmap* bm = bitmapInit(1024);
    
    DumpArvoreBitmap(arvHuf, bm);
    int index = 0;
    tAb* arvHuf2 = ReadArvoreBitmap(bm, &index);
    printf("\nARV LIDA +++++++++++++++++++++++++++++++++++++++++++++\n");
    ImprimeArvore(arvHuf2, -1);
    printf("\n");

    BinDumpBitmap(bm, argv[1], "arvore");
    bitmap* bmRead = BinReadBitmap("./arvore.bin");
    index = 0;
    printf("\nARVORE RECUPERADA DO BITMAP ++++++++++++++++++++++++++++\n");
    ImprimeArvore(ReadArvoreBitmap(bmRead, &index), -1);

    /*
    printf("imprimindo arvore original feita: \n");
    ImprimeArvore(arvHuf, -1);
    printf("\n");

    FILE *binFile = fopen("output.bin", "wb");
    if (binFile == NULL) {
        printf("Erro ao criar o arquivo binário.\n");
        exit(EXIT_FAILURE);
    }

    WriteBinAb(arvHuf, binFile);

    fclose(binFile);

    binFile = fopen("output.bin", "rb");
    if (binFile == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura.\n");
        exit(EXIT_FAILURE);
    }

    tAb* arvLida = ReadBinAb(binFile);

    printf("\nimprimindo arvore lida do arq bin: \n");
    ImprimeArvore(arvLida, -1);
    printf("\n");

    fclose(binFile);
    */

    // Desalocação e limpeza

    DesalocaTrilha(pilha);
    DesalocaTabelaCodificacao(table);
    DesalocaaAb(arvHuf);
    DesalocaaAb(arvHuf2);
    DesalocaLista(nos);
    bitmapLibera(bm);
    bitmapLibera(bmRead);
    free(vet);    

    return 0;
}