#ifndef _TLISTADADOS_H_
#define _TLISTADADOS_H_

#include "tAb.h"

typedef struct Trilha tTrilha;

#define ESQUERDA '0'
#define DIREITA '1'

tTrilha *CriaTrilha();

void DesalocaTrilha(tTrilha *p);

tTrilha *ClonaTrilha(tTrilha *p);

void PushTrilha(tTrilha *p, int c);

char PopTrilha(tTrilha *p);

int getSizeTrilha(tTrilha *p);

void PreencheTabelaCodificacao(char** table, tTrilha* t, tAb* ab);

char **CriaTabelaCodificacao();

void ImprimeTabela(char** table);

unsigned char* getInfoTrilha(tTrilha *t);

#endif