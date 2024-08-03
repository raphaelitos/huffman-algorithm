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

    FILE *saida = fopen(pathOut, "wb");
    if(!saida)TratarFalhaAlocacao("arqOut compacta");

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
    
    BinDumpBitmap(bmComp, saida);
    bitmapLibera(bmComp);

    DesalocaTrilha(pilha);
    DesalocaaAb(arvHuf);
    DesalocaLista(nos);
    free(vet);

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

            BinDumpBitmap(bmComp, saida);
            bitmapLibera(bmComp);
            bmComp = bitmapInit(UM_MEGA);
        }

        for(i; i < tamStr; i++){
            bitmapAppendLeastSignificantBit(bmComp, (code[i] - '0'));
        }
    }
    BinDumpBitmap(bmComp, saida);
    
    //compactacao finalizada; liberacao das estruturas
    bitmapLibera(bmComp);
    DesalocaTabelaCodificacao(table);

    fclose(entrada);
    fclose(saida);
}

/*int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Caminho para o arquivo não informado. Encerrando o programa.\n");
        return EXIT_FAILURE;
    }
    
    Compacta(argv[1]);
   
    return EXIT_SUCCESS;
}*/