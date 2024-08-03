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
    return nova;
}

static void desalocaCelDado(tCelDado *c){
    if(c) free(c);
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
        pop = NULL;
    }
    free(p);
}

void PushTrilha(tTrilha *p, unsigned char bit){
    if(!p) TratarStructNula("insere", "Trilha");

    tCelDado *nova = criaCelDado(bit);

    if(EstaVaziaTrilha(p)){
        p->prim = p->ult = nova;
    }
    else{
        p->ult->prox = nova;
        nova->ant = p->ult;
        p->ult = nova;
    }
    (p->tam)++;
}

unsigned char PopTrilha(tTrilha *p){
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
    else{
        p->prim = NULL;
    }
    (p->tam)--;
    desalocaCelDado(pop);
    pop = NULL;
    return c;
}

int getSizeTrilha(tTrilha *p){
    if(!p) TratarStructNula("getSize", "Trilha");
    return p->tam;
}

unsigned char **CriaTabelaCodificacao(){
    unsigned char **nova = (unsigned char**)calloc(TAM_ASCII, sizeof(unsigned char*));
    if(!nova)TratarFalhaAlocacao("TabelaCod");

    for(int i = 0; i < TAM_ASCII; i++){
        nova[i] = NULL;
    }

    return nova;
}

void DesalocaTabelaCodificacao(unsigned char **table){
    if(!table) return;

    for(int i = 0; i < TAM_ASCII; i++){
        free(table[i]);
        table[i] = NULL;
    }
    free(table);
}

unsigned char* getInfoTrilha(tTrilha *t){
    if(!t) TratarStructNula("getInfo", "trilha");
    if(EstaVaziaTrilha(t)) return NULL;

    unsigned char *path = (unsigned char*)calloc((getSizeTrilha(t) + 1), sizeof(unsigned char));
    tCelDado *c;
    path[getSizeTrilha(t)] = '\0';
    int i = 0;
    for(c = t->prim; c != NULL; c = c->prox){
        path[i] = c->info;
        i++;
        if(i > getSizeTrilha(t)){
            printf("Algo deu errado com o tamanho da pilha");
            exit(EXIT_FAILURE);
        }
    }
    return path;
}

void PreencheTabelaCodificacao(unsigned char** table, tTrilha* t, tAb* ab) {
    if(!ab)TratarStructNula("CriaTabelaCodificacao", "ab");

    if(ehFolha(ab)) {
        int index = (int)getChAb(ab);
        table[index] = getInfoTrilha(t);
        return;
    } 
    else {
        PushTrilha(t, ESQUERDA);
        PreencheTabelaCodificacao(table, t, GetSae(ab));
        PopTrilha(t);
        
        PushTrilha(t, DIREITA);
        PreencheTabelaCodificacao(table, t, GetSad(ab));
        PopTrilha(t);
    }
}