#ifndef _TLISTADADOS_H_
#define _TLISTADADOS_H_

#include "tAb.h"

typedef struct Trilha tTrilha;

tTrilha *CriaTrilha();

void DesalocaTrilha(tTrilha *p);

tTrilha *ClonaTrilha(tTrilha *p);

void InsereTrilha(tTrilha *p, int c);

char RetiraTrilha(tTrilha *p);

int getSizeTrilha(tTrilha *p);

void CriaTabelaCodificacao(tTrilha** table, tTrilha* pilha, tAb* ab);

void ImprimeTabela(tTrilha** table);

#endif