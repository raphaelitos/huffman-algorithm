#include <stdio.h>
#include <stdlib.h>
#include "tTrilha.h"
#include "utils.h"

/*
int main(){
    
    int *vet = IniciaVetAscII();
    ContaFreqCaracteres(vet, "teste.txt");

    FILE *arq = fopen("teste.txt", "r");
    if(!arq) TratarFalhaAlocacao("arquivoEntrada");

    tLista *nos = CriaListaNos(vet);
    tAb *arvHuf = CriaArvoreHuf(nos);
    tTrilha *p = CriaTrilha();

    unsigned char **tab = CriaTabelaCodificacao();
    PreencheTabelaCodificacao(tab, p, arvHuf);

    ImprimeTabela(tab);    
    
    DesalocaTabelaCodificacao(tab);
    DesalocaTrilha(p);
    DesalocaaAb(arvHuf);
    DesalocaLista(nos);
    free(vet);
    fclose(arq);

    return 0;
}*/