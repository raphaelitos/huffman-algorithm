#include <stdio.h>
#include <stdlib.h>
#include "tTrilha.h"
#include "utils.h"

typedef struct celDado tCelDado;

struct celDado{
    int info;
    tCelDado *prox;
};

static tCelDado *criaCelDado(int info){
    tCelDado *nova = (tCelDado*)calloc(1, sizeof(tCelDado));
    if(!nova)TratarFalhaAlocacao("celDado");
    nova->info = info;
    nova->prox = NULL;
}

static void desalocaCelDado(tCelDado *c){
    free(c);
}

struct Trilha{
    tCelDado *prim;
    tCelDado *ult;
    int tam;
};

static int EstaVaziaTrilha(tTrilha *p){
    if(!p)TratarStructNula("estaVazia", "Trilha");
    return !(p->tam);
}

tTrilha *CriaTrilha(){
    tTrilha *nova = (tTrilha*)calloc(1, sizeof(tTrilha));
    if(!nova) TratarFalhaAlocacao("Trilha");

    nova->prim = nova->ult = NULL;
    return nova;
}

void DesalocaTrilha(tTrilha *p){
    if(!p) TratarStructNula("desaloca", "Trilha");
    tCelDado *pop = NULL, *aux = p->prim;
    while(aux){
        pop = aux;
        aux = aux->prox;
        desalocaCelDado(pop);
    }
    free(p);
}

tTrilha *ClonaTrilha(tTrilha *p){
    if(!p)TratarStructNula("clona", "Trilha");
    tTrilha *clone = CriaTrilha();
    
    for(tCelDado *c = p->prim; c != NULL; c = c->prox){
        InsereTrilha(clone, c->info);
    }
    
    return clone;
}

void InsereTrilha(tTrilha *p, int bit){
    if(!p) TratarStructNula("insere", "Trilha");

    tCelDado *nova = criaCelDado(bit);

    if(EstaVaziaTrilha(p)){
        p->prim = p->ult = nova;
    }
    else{
        nova->prox = p->prim;
        p->prim = nova;
    }
    (p->tam)++;
}

char RetiraTrilha(tTrilha *p){
    if(!p) TratarStructNula("retira", "Trilha");
    if(EstaVaziaTrilha(p)){
        return '\0';
    }
    tCelDado *pop = p->prim;
    int info = p->prim->info;
    p->prim = p->prim->prox;
    (p->tam)--;
    desalocaCelDado(pop);
}

int getSizeTrilha(tTrilha *p){
    if(!p) TratarStructNula("getSize", "Trilha");
    return p->tam;
}

void CriaTabelaCodificacao(tTrilha** table, tTrilha* pilha, tAb* ab) {
    if(!ab)TratarStructNula("CriaTabelaCodificacao", "ab");

    int index = (int) getChAb(ab);
    if(ehFolha(ab)) {
        table[index] = ClonaTrilha(pilha);

    } else {
        InsereTrilha(pilha, 0);
        CriaTabelaCodificacao(table, pilha, GetSae(ab));
        InsereTrilha(pilha, 1);
        CriaTabelaCodificacao(table, pilha, GetSad(ab));
    }

    RetiraTrilha(pilha);
}

static void ImprimePilha(tTrilha* pilha) {
    tCelDado* atual = pilha->prim;
    while (atual) {
        printf("%d", atual->info);
        atual = atual->prox;
    }
}

void ImprimeTabela(tTrilha** table) {
    for (int i = 0; i < 127; i++) {
        if (table[i] != NULL) {
            printf("Tabela[%c]: ", (char)i);
            ImprimePilha(table[i]);
            printf("\n");
        }
    }
}