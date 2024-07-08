#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tFila.h"
#include "utils.h"
#include "amostra.h"

#define IDADE_IDOSO 60

typedef struct celula tCelula;

struct celula{
    tCelula *prox;
    Amostra *amostra;
};

static tCelula *criaCelula(Amostra *a){
    if(!a) TratarStructNula("criacelula","amostra");

    tCelula *c = (tCelula *)calloc(1, sizeof(tCelula));
    if(!c)TratarFalhaAlocacao("celula");

    c->amostra = a;
    c->prox = NULL;

    return c;
}

static void desalocaCelula(tCelula *c){
    if(!c) TratarStructNula("desaloca", "celula");
    free(c);
}

static void imprimeCelula(tCelula *c){
    if(!c)TratarStructNula("imprime", "celula");
    imprimeAmostra(c->amostra);
}

struct fila{
    tCelula *prim;
    tCelula *ult;
    int tamanho;
};

tFila *criaFila(){
    tFila *f = (tFila*)calloc(1, sizeof(tFila));
    if(!f) TratarFalhaAlocacao("fila");

    f->prim = f->ult = NULL;
    return f;
}

void desalocaFila(tFila *f){
    if(!f) TratarStructNula("desaloca", "fila");
    
    tCelula *cel = f->prim, *pop = NULL;
    while(cel != NULL){
        pop = cel;
        cel = cel->prox;
        liberaAmostra(pop->amostra);
        desalocaCelula(pop);
    }
    free(f);
}

static int ehVelho(Amostra *a){
    if(!a)TratarStructNula("ehVelho", "amostra");
    return(retornaIdade(a) >= IDADE_IDOSO);
}

static int estaVaziaFila(tFila *f){
    if(!f)TratarStructNula("estavazia", "fila");
    return f->prim == NULL;
}

void insereFila(tFila *f, Amostra *a){
    if(!f) TratarStructNula("insere", "fila");
    
    tCelula *c = criaCelula(a);

    if(estaVaziaFila(f)){
        f->prim = f->ult = c;
    }
    
    else if(ehVelho(a)){
        c->prox = f->prim;
        f->prim = c;
    }

    else{
        f->ult->prox = c;
        f->ult = c;
    }
    (f->tamanho)++;
}

Amostra *retiraFila(tFila *f){
    if(!f)TratarStructNula("retira", "fila");

    if(estaVaziaFila(f)){
        printf("Sua fila ja esta vazia!\n");
        Amostra *a = NULL;
        return a;
    }

    Amostra *pop = f->prim->amostra;
    tCelula *cel = f->prim;
    f->prim = cel->prox;
    
    (f->tamanho)--;
    desalocaCelula(cel);
    return pop;
}

void imprimeFila(tFila *f){
    if(!f)TratarStructNula("imprime", "fila");
    for(tCelula *c = f->prim; c != NULL; c = c->prox){
        imprimeCelula(c);
    }
}

int getTamanhoFila(tFila *f){
    if(!f)TratarStructNula("getTamanho", "fila");
    return f->tamanho;
}