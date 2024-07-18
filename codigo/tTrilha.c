#include <stdio.h>
#include <stdlib.h>
#include "tTrilha.h"
#include "utils.h"

typedef struct celDado tCelDado;

struct celDado{
    unsigned char info;
    tCelDado *prox;
    tCelDado *ant;
};

static tCelDado *criaCelDado(unsigned char info){
    tCelDado *nova = (tCelDado*)calloc(1, sizeof(tCelDado));
    if(!nova)TratarFalhaAlocacao("celDado");
    nova->info = info;
    nova->prox = nova->ant = NULL;
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

    nova->prim = NULL;
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
        pushTrilha(clone, c->info);
    }
    
    return clone;
}

void pushTrilha(tTrilha *p, unsigned char bit){
    if(!p) TratarStructNula("insere", "Trilha");

    tCelDado *nova = criaCelDado(bit);

    if(EstaVaziaTrilha(p)){
        p->prim = p->ult =nova;
    }
    else{
        p->ult->prox = nova;
        nova->ant = p->ult;
        p->ult = nova;
    }
    (p->tam)++;
}

char PopTrilha(tTrilha *p){
    if(!p) TratarStructNula("retira", "Trilha");
    if(EstaVaziaTrilha(p)){
        return '\0';
    }
    tCelDado *pop = p->ult;
    char c = pop->info;
    p->ult = p->ult->ant;
    if(p->ult){
        p->ult->prox = NULL;
    }
    (p->tam)--;
    desalocaCelDado(pop);
    return c;
}

int getSizeTrilha(tTrilha *p){
    if(!p) TratarStructNula("getSize", "Trilha");
    return p->tam;
}

unsigned char* getInfoTrilha(tTrilha *t){
    if(!t) TratarStructNula("getInfo", "trilha");
    if(EstaVaziaTrilha(t)) return NULL;

    unsigned char *path = (unsigned char*)calloc((getSizeTrilha(t) + 1), sizeof(unsigned char));
    tCelDado *c;
    int i = 0;
    for(c = t->prim; c != NULL; c = c->prox){
        path[i] = c->info;
        i++;
    }
    path[getSizeTrilha(t) + 1] = '\0';
    return path;
}

void PreencheTabelaCodificacao(char** table, tTrilha* t, tAb* ab) {
    if(!ab)TratarStructNula("CriaTabelaCodificacao", "ab");

    int index = (int)getChAb(ab);
    if(ehFolha(ab)) {
        table[index] = getInfoTrilha(t);

    } else {
        pushTrilha(t, 0);
        CriaTabelaCodificacao(table, t, GetSae(ab));
        pushTrilha(t, 1);
        CriaTabelaCodificacao(table, t, GetSad(ab));
    }

    popTrilha(t);
}

char **CriaTabelaCodificacao(){
    char **nova = (char**)calloc(256, sizeof(unsigned char));
}

static void ImprimePilha(tTrilha* pilha) {
    tCelDado* atual = pilha->prim;
    while (atual) {
        printf("%c", atual->info);
        atual = atual->prox;
    }
}

void ImprimeTabela(char** table) {
    for (int i = 0; i < 127; i++) {
        if (table[i] != NULL) {
            printf("Tabela[%c]: ", (char)i);
            //ImprimePilha(table[i]);
            printf("%s\n", table[i]);
        }
    }
}