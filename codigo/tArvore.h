#ifndef _TARVORE_H_
#define _TARVORE_H_

#include "tAluno.h"

typedef struct arvore tArvore;

tArvore *criaVazia();

tArvore *criaArvore(tAluno *a, tArvore *sae, tArvore *sad);

void desalocaArvore(tArvore *a);

int calculaFolhas(tArvore* a);

int calculaOcorrencias(tArvore* a , char* nome); 

int calculaAltura(tArvore* a);

int pertenceAluno(tArvore* a , char* nome);

void imprimeArvore(tArvore *a);

#endif