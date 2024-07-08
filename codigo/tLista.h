#ifndef _TLISTA_H_
#define _TLISTA_H_

typedef struct lista tLista;

#include "tAb.h"

tLista* CriaLista();

void DesalocaLista(tLista* l);

void InsereLista(tLista *l, tAb *ab);

void OrdenaLista(tLista *l);

#endif