#include <stdio.h>
#include <stdlib.h>
#include "tPilhaDados.h"
#include "utils.h"

typedef struct celDado{
    char info;
    tCelDado *prox;
}tCelDado;

static tCelDado *criaCelDado(char info){
    tCelDado *nova = (tCelDado*)calloc(1, sizeof(tCelDado));
    if(!nova)TratarFalhaAlocacao("celDado");
    nova->info = info;
    nova->prox = NULL;
}

static void desalocaCelDado(tCelDado *c){
    free(c);
}

struct pilhaDados{
    tCelDado *prim;
    tCelDado *ult;
    int tam;
};

static int EstaVaziaPilhaDados(tPilhaDados *p){
    if(!p)TratarStructNula("estaVazia", "pilhaDados");
    return !(p->tam);
}

tPilhaDados *CriaPilhaDados(){
    tPilhaDados *nova = (tPilhaDados*)calloc(1, sizeof(tPilhaDados));
    if(!nova) TratarFalhaAlocacao("pilhaDados");

    nova->prim = nova->ult = NULL;
    return nova;
}

void DesalocaPilhaDados(tPilhaDados *p){
    if(!p) TratarStructNula("desaloca", "pilhaDados");
    tCelDado *pop = NULL, *aux = p->prim;
    while(aux){
        pop = aux;
        aux = aux->prox;
        desalocaCelDado(pop);
    }
    free(p);
}

tPilhaDados *ClonaPilhaDados(tPilhaDados *p){
    if(!p)TratarStructNula("clona", "pilhaDados");
    tPilhaDados *clone = CriaPilhaDados();
    
    for(tCelDado *c = p->prim; c != NULL; c = c->prox){
        InserePilhaDados(clone, c->info);
    }
    
    return clone;
}

void InserePilhaDados(tPilhaDados *p, char c){
    if(!p) TratarStructNula("insere", "pilhaDados");

    tCelDado *nova = criaCelDado(c);

    if(EstaVaziaPilhaDados(p)){
        p->prim = p->ult = nova;
    }
    else{
        nova->prox = p->prim;
        p->prim = nova;
    }
    (p->tam)++;
}

char RetiraPilhaDados(tPilhaDados *p){
    if(!p) TratarStructNula("retira", "pilhaDados");
    if(EstaVaziaPilhaDados(p)){
        return '\0';
    }
    tCelDado *pop = p->prim;
    char info = p->prim->info;
    p->prim = p->prim->prox;
    (p->tam)--;
    desalocaCelDado(pop);
}

int getSizePilhaDados(tPilhaDados *p){
    if(!p) TratarStructNula("getSize", "pilhaDados");
    return p->tam;
}