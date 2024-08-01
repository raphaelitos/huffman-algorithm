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
    bitmap *bmComp = bitmapInit(UM_MEGA/2);
    DumpArvoreBitmap(arvHuf, bmComp);
    
    printf("dump de bitmap com a arvore\n");
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
        printf("char lido: %c\n", byte);
        printf("Tamanho da string: %d\n", tamStr);

        if((tamBm + tamStr) >= max){ //talvez seja apenas maior que...
            
            for(i = 0; i < (max - tamBm); i++){
                bitmapAppendLeastSignificantBit(bmComp, (code[i] - '0'));
                printf("valor do bit add ao bitmap: %d\n", (code[i] - '0'));
            }

            printf("Dump com bitmap cheio (se tudo estiver certo)\n");
            BinDumpBitmap(bmComp, pathOut, 1);
            bitmapLibera(bmComp);
            bmComp = bitmapInit(UM_MEGA);
            //ResetBitmap(bmComp);
        }

        for(i; i < tamStr; i++){
            bitmapAppendLeastSignificantBit(bmComp, (code[i] - '0'));
            printf("valor do bit add ao bitmap: %d\n", (code[i] - '0'));
        }
    }
    printf("Dump de bitmap compactado\n");
    BinDumpBitmap(bmComp, pathOut, 1);
    
    ImprimeArvore(arvHuf, -1);

    bitmapLibera(bmComp);
    DesalocaTrilha(pilha);
    DesalocaTabelaCodificacao(table);
    DesalocaaAb(arvHuf);
    DesalocaLista(nos);
    free(vet);
    fclose(entrada);
}

static void DescompactaBitmap(bitmap* bm, char* pathOut, tAb* arvHuf) {
    tAb* aux = arvHuf;
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
            printf("dump de bitmap descompactado\n");
            BinDumpBitmap(bmDescomp, pathOut, 0);
            bitmapLibera(bmDescomp);
            bmDescomp = bitmapInit(UM_MEGA);
            //ResetBitmap(bmDescomp);
        }
        if(ehFolha(aux)) {
            printf("Add byte descomp\n");
            bitmapAppendByte(bmDescomp, getChAb(aux));
            printf("char encontrado: %c\n", getChAb(aux));
            aux = arvHuf; //reset da árvore para o próximo caractere
        }
    }

    //Salva o ultimo bitmap descompactado se ele nao tiver enchido
    if (bitmapGetLength(bmDescomp) > 0) {
        printf("dump do ultimo bitmap descomp\n");
        BinDumpBitmap(bmDescomp, pathOut, 0);
    }
    
    bitmapLibera(bmDescomp);
}

void Descompacta(char* nomeArquivoIn) {
    if(!nomeArquivoIn)TratarStructNula("Descompacta", "char*");

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

    printf("lendo a arvore no cabecalho do arquivo\n");
    bitmap* bm = BinReadBitmap(arqIn);

    unsigned int index = 0;
    tAb* arvHuf = ReadArvoreBitmap(bm, &index);
    ImprimeArvore(arvHuf, -1);
    bitmapLibera(bm);

    while(1){
        printf("lendo bitmap de conteudo do arquivo\n");
        bm = BinReadBitmap(arqIn);
        
        if(bm == NULL) break;
        printf("bitmap lido\n");

        DescompactaBitmap(bm, pathOut, arvHuf);

        bitmapLibera(bm);
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
        printf("Teste bem-sucedido: O arquivo descompactado eh igual ao original.\n");
    } else {
        printf("Teste falhou: O arquivo descompactado eh diferente do original.\n");
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
    char outputPath[] = "teste.txt.out";    
   
    
    //printf("\nComecou a compactar\n");
    //Compacta(inputPath);
    
    printf("\nComecou a descompactar\n");
    Descompacta(inputPath);
    /*
    FILE *original = fopen(inputPath, "rb");
    FILE *descompacted = fopen(outputPath, "rb");
    
    // Verifica se o arquivo descompactado é igual ao arquivo original
    TestaArquivos(original, descompacted);

    fclose(original);
    fclose(descompacted);
    */
    return EXIT_SUCCESS;
}