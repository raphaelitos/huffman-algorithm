#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLista.h"
#include "tTrilha.h"
#include "utils.h"

void Compacta(char *nomeArquivo, char **table){
    
    bitmap *bmComp = bitmapInit(1024);

    FILE *entrada = fopen(nomeArquivo, "rb");
    if(!entrada)TratarFalhaAlocacao("arqIn compacta");

    char pathOut[strlen(nomeArquivo) + strlen(EXTENSAO) + 2];
    sprintf(pathOut, "%s%s", nomeArquivo, EXTENSAO);

    unsigned char byte;
    while(1){
        fread(&byte, sizeof(unsigned char), 1, entrada);

        if((int)byte == EOF){
            break;
        }

        unsigned char *code = table[(unsigned int)byte];
        int tamStr = strlen(code);
        int tamBm = bitmapGetLength(bmComp);
        int max = bitmapGetMaxSize(bmComp);
        int i = 0;

        if((tamBm + tamStr) >= max){
            
            for(i = 0; i < (max - tamBm); i++){
                bitmapAppendLeastSignificantBit(bmComp, (code[i] - '0'));
            }

            BinDumpBitmap(bmComp, pathOut);
            ResetBitmap(bmComp);
        }

        for(i; i < tamStr; i++){
            bitmapAppendLeastSignificantBit(bmComp, (code[i] - '0'));
        }
    }
    
    BinDumpBitmap(bmComp, pathOut);
    bitmapLibera(bmComp);
    fclose(entrada);
}


void Descompacta(bitmap* bm, int inic, char* path, tAb* arvHuf) {
    tAb* aux = arvHuf;
    int bit = 0;
    bitmap* bmDescomp = bitmapInit(bitmapGetMaxSize(bm));    

    while(inic < bitmapGetLength(bm)) {
        if(bitmapGetLength(bmDescomp) >= bitmapGetMaxSize(bmDescomp)) {
            BinDumpBitmap(bmDescomp, path);
        }
        if(ehFolha(aux)) {
            bitmapAppendByte(bmDescomp, getChAb(aux));
            aux = arvHuf; //reset da árvore para o próximo caractere
        }

        bit = bitmapGetBit(bm, inic);
        inic++;
        if(bit == 0) aux = GetSae(aux);
        else aux = GetSad(aux);
    }

    //Salva o ultimo bitmap descompactado que ficou incompleto
    if (bitmapGetLength(bmDescomp) > 0) {
        BinDumpBitmap(bmDescomp, path);
    }
}

int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("Caminho para arquivos não informado. Encerrando programa.\n");
        exit(EXIT_FAILURE);
    }

    int* vet = IniciaVetAscII();
    //char path[1000];
    //sprintf(path, "%s/input/biblia.txt", argv[1]);

    ContaFreqCaracteres(vet, argv[1]);
    //PrintVetInt(vet, TAM_ASCII);

    tLista *nos = CriaListaNos(vet);
    tAb *arvHuf = CriaArvoreHuf(nos);

    tTrilha* pilha = CriaTrilha();
    unsigned char** table = CriaTabelaCodificacao();
    PreencheTabelaCodificacao(table, pilha, arvHuf);
    //ImprimeTabela(table);

    printf("ARV ORIGINAL +++++++++++++++++++++++++++++++++++++++++++++\n");
    ImprimeArvore(arvHuf, -1);
    
    bitmap* bm = bitmapInit(1024);
    
    DumpArvoreBitmap(arvHuf, bm);
    int index = 0;
    tAb* arvHuf2 = ReadArvoreBitmap(bm, &index);
    printf("\nARV LIDA +++++++++++++++++++++++++++++++++++++++++++++\n");
    ImprimeArvore(arvHuf2, -1);
    printf("\n");

    BinDumpBitmap(bm, "arvore.bin");
    bitmap* bmRead = BinReadBitmap("arvore.bin");
    index = 0;
    tAb *abRd = ReadArvoreBitmap(bmRead, &index);
    printf("\nARVORE RECUPERADA DO BITMAP ++++++++++++++++++++++++++++\n");
    ImprimeArvore(abRd, -1);

    printf("\nTESTE BITMAPS ============\n");
    printf("\nORIGINAL\n");
    printMapContents(bm);
    printf("\nLIDO\n");
    printMapContents(bmRead);

    // Desalocação e limpeza

    DesalocaTrilha(pilha);
    DesalocaTabelaCodificacao(table);
    DesalocaaAb(arvHuf);
    DesalocaaAb(arvHuf2);
    DesalocaaAb(abRd);
    DesalocaLista(nos);
    bitmapLibera(bm);
    bitmapLibera(bmRead);
    free(vet);    

    return 0;
}