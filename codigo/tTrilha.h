#ifndef _TLISTADADOS_H_
#define _TLISTADADOS_H_

#include "tAb.h"

typedef struct Trilha tTrilha;

tTrilha *CriaTrilha();

void DesalocaTrilha(tTrilha *p);

tTrilha *ClonaTrilha(tTrilha *p);

void PushTrilha(tTrilha *p, unsigned char c);

char PopTrilha(tTrilha *p);

int getSizeTrilha(tTrilha *p);

unsigned char **CriaTabelaCodificacao();

void DesalocaTabelaCodificacao(unsigned char **table);

unsigned char* getInfoTrilha(tTrilha *t);

void PreencheTabelaCodificacao(unsigned char** table, tTrilha* t, tAb* ab);

void ImprimeTabela(unsigned char** table);

#endif