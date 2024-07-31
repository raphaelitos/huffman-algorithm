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
    
    printf("Impressao da tabela de codificacao\n");
    ImprimeTabela(table);

    //colocando a arvore no binario
    bitmap *bmComp = bitmapInit(UM_MEGA);
    DumpArvoreBitmap(arvHuf, bmComp);
    
    printf("dump de bitmap com a arvore\n");
    BinDumpBitmap(bmComp, pathOut);
    ResetBitmap(bmComp);

    //Conteudo do arquivo compactado

    FILE *entrada = fopen(nomeArquivo, "rb");
    if(!entrada)TratarFalhaAlocacao("arqIn compacta");

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

            printf("Dump com bitmap cheio (se tudo estiver certo)\n");
            BinDumpBitmap(bmComp, pathOut);
            ResetBitmap(bmComp);
        }

        for(i; i < tamStr; i++){
            bitmapAppendLeastSignificantBit(bmComp, (code[i] - '0'));
        }
    }
    printf("Dump de bitmap compactado\n");
    BinDumpBitmap(bmComp, pathOut);
    
    bitmapLibera(bmComp);
    DesalocaTrilha(pilha);
    DesalocaTabelaCodificacao(table);
    DesalocaaAb(arvHuf);
    DesalocaLista(nos);
    free(vet);
    fclose(entrada);
}

static void DescompactaBitmap(bitmap* bm, unsigned int inic, char* pathOut, tAb* arvHuf) {
    tAb* aux = arvHuf;
    int bit = 0;
    bitmap* bmDescomp = bitmapInit(bitmapGetMaxSize(bm));    

    while(inic < bitmapGetLength(bm)) {
        if(bitmapGetLength(bmDescomp) >= bitmapGetMaxSize(bmDescomp)) {
            BinDumpBitmap(bmDescomp, pathOut);
        }
        if(ehFolha(aux)) {
            printf("Add byte descomp\n");
            bitmapAppendByte(bmDescomp, getChAb(aux));
            aux = arvHuf; //reset da árvore para o próximo caractere
        }

        bit = (int)bitmapGetBit(bm, inic);
        inic++;
        if(bit == 0) aux = GetSae(aux);
        else aux = GetSad(aux);
    }

    //Salva o ultimo bitmap descompactado que ficou incompleto
    if (bitmapGetLength(bmDescomp) > 0) {
        BinDumpBitmap(bmDescomp, pathOut);
    }
    bitmapLibera(bmDescomp);
}

void Descompacta(char* nomeArquivoIn) {
    if(!nomeArquivoIn)TratarStructNula("Descompacta", "char*");
    
    char pathOut[strlen(nomeArquivoIn) - strlen(EXTENSAO) + 1];
    sscanf(nomeArquivoIn, "%s.comp", pathOut);


    FILE *arqIn = fopen(nomeArquivoIn, "rb");
    if(!arqIn) TratarFalhaAlocacao("arqIn em descompacta");

    printf("lendo a arvore no cabecalho do arquivo\n");
    bitmap* bm = BinReadBitmap(arqIn);

    unsigned int index = 0;
    tAb* arvHuf = ReadArvoreBitmap(bm, &index);
    bitmapLibera(bm);

    while(1){
        printf("lendo bitmap de conteudo do arquivo\n");
        bm = BinReadBitmap(arqIn);
        
        if(bm == NULL) break;

        DescompactaBitmap(bm, index, pathOut, arvHuf);

        bitmapLibera(bm);
        index = 0;
    }
    
    DesalocaaAb(arvHuf);
    fclose(arqIn);
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
    char compactedPath[strlen(inputPath) + strlen(EXTENSAO) + 1];
    sprintf(compactedPath, "%s%s", inputPath, EXTENSAO);
    char outputPath[] = "output.txt";    
    
    printf("\nComecou a compactar\n");
    Compacta(inputPath);
    
    printf("\nComecou a descompactar\n");
    Descompacta(compactedPath);

    FILE *original = fopen(inputPath, "rb");
    FILE *descompacted = fopen(outputPath, "rb");
    
    // Verifica se o arquivo descompactado é igual ao arquivo original
    TestaArquivos(original, descompacted);

    fclose(original);
    fclose(descompacted);
    
    return EXIT_SUCCESS;
}