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
        PushTrilha(clone, c->info);
    }
    
    return clone;
}

void PushTrilha(tTrilha *p, unsigned char bit){
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

    int index = (int)getChAb(ab);
    if(ehFolha(ab)) {
        table[index] = getInfoTrilha(t);
        PopTrilha(t);
    } 
    else {
        PushTrilha(t, ESQUERDA);
        PreencheTabelaCodificacao(table, t, GetSae(ab));
        PushTrilha(t, DIREITA);
        PreencheTabelaCodificacao(table, t, GetSad(ab));
    }

}

static void ImprimePilha(tTrilha* pilha) {
    tCelDado* atual = pilha->prim;
    while (atual) {
        printf("%c", atual->info);
        atual = atual->prox;
    }
}

void ImprimeTabela(unsigned char** table) {
    for (int i = 0; i < 127; i++) {
        if (table[i] != NULL) {
            printf("Tabela[%c]: ", (char)i);
            //ImprimePilha(table[i]);
            printf("%s\n", table[i]);
        }
    }
}