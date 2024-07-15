#ifndef _TLISTADADOS_H_
#define _TLISTADADOS_H_

#include "tAb.h"

typedef struct pilhaDados tPilhaDados;

tPilhaDados *CriaPilhaDados();

void DesalocaPilhaDados(tPilhaDados *p);

tPilhaDados *ClonaPilhaDados(tPilhaDados *p);

void InserePilhaDados(tPilhaDados *p, int c);

char RetiraPilhaDados(tPilhaDados *p);

int getSizePilhaDados(tPilhaDados *p);

void CriaTabelaCodificacao(tPilhaDados** table, tPilhaDados* pilha, tAb* ab);

void ImprimeTabela(tPilhaDados** table);

#endif