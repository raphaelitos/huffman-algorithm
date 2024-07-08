#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char ch = '\0';
    
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

int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("caminho para arquivos nao informado. Encerrando programa\n");
        exit(EXIT_FAILURE);
    }
    int* vet = IniciaVetAscII();
    
    char path[1000];
    sprintf(path, "%s/text.txt", argv[1]);
    
    ContaFreqCaracteres(vet, path);
    PrintVetInt(vet, TAM_ASCII);
    
    free(vet);    
}