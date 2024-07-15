#ifndef _TLISTADADOS_H_
#define _TLISTADADOS_H_

typedef struct pilhaDados tPilhaDados;


tPilhaDados *CriaPilhaDados();

void DesalocaPilhaDados(tPilhaDados *p);

tPilhaDados *ClonaPilhaDados(tPilhaDados *p);

void InserePilhaDados(tPilhaDados *p, char c);

char *RetiraPilhaDados(tPilhaDados *p);

int getSizePilhaDados(tPilhaDados *p);

#endif