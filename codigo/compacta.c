#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLista.h"
#include "tTrilha.h"
#include "utils.h"

void Compacta(char *nomeArquivo, unsigned char **table){
    
    bitmap *bmComp = bitmapInit(UM_MEGA);

    FILE *entrada = fopen(nomeArquivo, "rb");
    if(!entrada)TratarFalhaAlocacao("arqIn compacta");

    char pathOut[strlen(nomeArquivo) + strlen(EXTENSAO) + 2];
    sprintf(pathOut, "%s%s", nomeArquivo, EXTENSAO);

    unsigned char byte;
    while(1){
        size_t bytesRead = fread(&byte, sizeof(unsigned char), 1, entrada);

        if(bytesRead != 1) break;

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

static void DescompactaBitmap(bitmap* bm, int inic, char* pathOut, tAb* arvHuf) {
    tAb* aux = arvHuf;
    int bit = 0;
    bitmap* bmDescomp = bitmapInit(bitmapGetMaxSize(bm));    

    while(inic < bitmapGetLength(bm)) {
        if(bitmapGetLength(bmDescomp) >= bitmapGetMaxSize(bmDescomp)) {
            BinDumpBitmap(bmDescomp, pathOut);
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
        BinDumpBitmap(bmDescomp, pathOut);
    }
}

void Descompacta(char* nomeArquivoIn) {
    char pathOut[strlen(nomeArquivoIn) - strlen(EXTENSAO) + 1];
    sscanf(nomeArquivoIn, "%s.comp", pathOut);

    int index = 0;
    bitmap* bm = BinReadBitmap(nomeArquivoIn);
    tAb* arvHuf = ReadArvoreBitmap(bm, &index);
    bitmapLibera(bm);

    while(1){
        bm = BinReadBitmap(nomeArquivoIn);
        if(bm == NULL) break;

        DescompactaBitmap(bm, index, pathOut, arvHuf);

        bitmapLibera(bm);
        index = 0;
    }
}

void TestaArquivos(FILE *a1, FILE *a2){
    char ch1, ch2;
    if (!a1 || !a2) {
        TratarStructNula("testaArquivos", "arquivos");
    }
    int result = 1;
    while (fread(&ch1, sizeof(char), 1, a1) && fread(&ch2, sizeof(char), 1, a2)) {
        if (ch1 != ch2) {
            result = 0;
            break;
        }
    }
    if (result && feof(a1) && feof(a2)) {
        printf("Teste bem-sucedido: O arquivo descompactado é igual ao original.\n");
    } else {
        printf("Teste falhou: O arquivo descompactado é diferente do original.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Caminho para o arquivo não informado. Encerrando o programa.\n");
        return EXIT_FAILURE;
    }

    char *inputPath = argv[1];
    char compactedFile[strlen(inputPath) + strlen(EXTENSAO) + 1];
    sprintf(compactedFile, "%s%s", inputPath, EXTENSAO);
    char outputPath[] = "output.txt";

    // Inicializa as estruturas necessárias
    int *vet = IniciaVetAscII();
    ContaFreqCaracteres(vet, inputPath);

    tLista *nos = CriaListaNos(vet);
    tAb *arvHuf = CriaArvoreHuf(nos);

    tTrilha *pilha = CriaTrilha();
    unsigned char **table = CriaTabelaCodificacao();
    PreencheTabelaCodificacao(table, pilha, arvHuf);

    //colocando a arvore no binario
    bitmap* bm = bitmapInit(UM_MEGA);
    DumpArvoreBitmap(arvHuf, bm);
    BinDumpBitmap(bm, compactedFile);
    bitmapLibera(bm);

    ImprimeTabela(table);
    printf("Comecou a compactar\n");
    // Compacta o arquivo de entrada
    Compacta(inputPath, table);

    printf("Comecou a descompactar\n");
    // Descompacta o arquivo compactado
    Descompacta(compactedFile);

    // Verifica se o arquivo descompactado é igual ao arquivo original
    FILE *original = fopen(inputPath, "rb");
    FILE *descompacted = fopen(outputPath, "rb");
    
    TestaArquivos(original, descompacted);

    fclose(original);
    fclose(descompacted);

    // Desaloca as estruturas
    DesalocaTrilha(pilha);
    DesalocaTabelaCodificacao(table);
    DesalocaaAb(arvHuf);
    DesalocaLista(nos);
    free(vet);

    return EXIT_SUCCESS;
}