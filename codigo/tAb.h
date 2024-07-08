#ifndef _tAb_H_
#define _tAb_H_

typedef struct ab tAb;

/// @brief cria um ponteiro da estrutura tAb
/// @return um ponteiro de tAb com valor NULL
tAb *criaAb();

/// @brief libera a memoria utilizada
/// por uma estrutura tAb
/// @param abb a arvore que se deseja desalocar
void desalocaaAb(tAb *ab);

int getFreqAb(tAb *ab);

char getChAb(tAb *ab);

#endif