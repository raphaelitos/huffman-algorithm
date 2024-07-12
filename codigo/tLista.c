#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLista.h"
#include "utils.h"

typedef struct celula tCelula;

struct celula{
    tAb *ab;
    tCelula *prox;
    tCelula *ant;
};

static tCelula *CriaCelula(tAb *ab){
    if(!ab)TratarStructNula("criaCelula", "ab");
    tCelula *c = (tCelula*)calloc(1, sizeof(tCelula));
    if(!c)TratarFalhaAlocacao("celula");
    c->ab = ab;
    c->prox = c->ant = NULL;
}

static void DesalocaCelula(tCelula *c){
    free(c);
}

struct lista{
    tCelula *prim;
    tCelula *ult;
};

static int EstaVaziaLista(tLista *l){
    if(!l)TratarStructNula("estaVazia", "lista");
    return (l->prim == NULL);
}

tLista* CriaLista(){
    tLista *l = (tLista*)calloc(1, sizeof(tLista));
    if(!l)TratarFalhaAlocacao("lista");
    l->prim = l->ult = NULL;

    return l;
}

void DesalocaLista(tLista* l){
    if(!l) return;
    tCelula *aux = l->prim, *pop = NULL;
    while(aux){
        pop = aux;
        aux = aux->prox;
        DesalocaCelula(pop);
    }
    free(l);
}

void InsereLista(tLista *l, tAb *ab){
    if(!l || !ab) TratarStructNula("insere", "lista ou ab");
    
    tCelula *nova = CriaCelula(ab);

    if(EstaVaziaLista(l)){
        l->prim = l->ult = nova;
        nova->ant = nova->prox = NULL;
        return;
    }

    tCelula *aux = l->prim;

    while(aux){
        if(getFreqAb(nova->ab) <= getFreqAb(aux->ab)){
            
            nova->ant = aux->ant;
            nova->prox = aux;
            
            if(aux->ant){
                aux->ant->prox = nova;
            }
            else{//primeira posicao
                l->prim = nova;
            }
            
            aux->ant = nova;

            return;
        }
        aux = aux->prox;
    }
    //ultima posicao
    nova->ant = l->ult;
    l->ult->prox = nova;
    l->ult = nova;
    nova->prox = NULL;

    //outro jeito de fazer isso
    /*
    while(aux && (getFreqAb(nova->ab) > getFreqAb(aux->ab))){
        aux = aux->prox;
    }
    if(aux){
        nova->ant = aux->ant;
        nova->prox = aux;
        
        if(aux->ant){
            aux->ant->prox = nova;
        }
        else{//primeira posicao
            l->prim = nova;
        }
        
        aux->ant = nova;
    }
    else{//ultima posicao
        nova->ant = l->ult;
        l->ult->prox = nova;
        l->ult = nova;
    }*/

}