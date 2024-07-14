#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLista.h"
#include "utils.h"

#define TAM_ASCII 128

int *IniciaVetAscII(){
    int *vet = (int*)calloc(TAM_ASCII, sizeof(int));
    if(!vet) exit(EXIT_FAILURE);
    return vet;
}

void ContaFreqCaracteres(int *vet, char *path){
    FILE *arq = fopen(path, "r");
    if(!arq) exit(EXIT_FAILURE);
    
    int c = 0;

    while(1){
        c = fgetc(arq);
        if(c == EOF) break;
        //printf("Caractere lido: %c (ASCII: %d)\n", (char)c, c);
        (vet[c])++;
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
    printf("]");
}

tLista* CriaListaNos(int* vet){
    if(!vet) TratarStructNula("PreencheNos", "vet");

    tLista *lista = CriaLista();
    tAb *aux = NULL;
    
    for(int i = 0; i < TAM_ASCII; i ++){
        if(vet[i]){
            aux = CriaAb((unsigned char)i, (unsigned int)vet[i], NULL, NULL);
            InsereLista(lista, aux);
        }
    }

    return lista;
}

tAb* CriaArvoreHuf(tLista* nos){
    if(!nos)TratarStructNula("CriaArvHuf", "lista");
    
    if(getSizeLista(nos) == 0) return NULL;

    if(getSizeLista(nos) == 1){
        return RetiraLista(nos);
    }

    tAb *a1 = RetiraLista(nos);
    tAb *a2 = RetiraLista(nos);
    tAb *nova = JoinAb(a1, a2);
    InsereLista(nos, nova);
    
    return CriaArvoreHuf(nos);
}

int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("Caminho para arquivos não informado. Encerrando programa.\n");
        exit(EXIT_FAILURE);
    }

    int* vet = IniciaVetAscII();

    char path[1000];
    sprintf(path, "%s/text.txt", argv[1]);
    
    ContaFreqCaracteres(vet, path);

    tLista *nos = CriaListaNos(vet);
    tAb *arvHuf = CriaArvoreHuf(nos);
    //PrintVetInt(vet, TAM_ASCII);

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

    DesalocaaAb(arvHuf);
    DesalocaaAb(arvLida);
    DesalocaLista(nos);
    free(vet);    

    return 0;
}