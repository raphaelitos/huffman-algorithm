#ifndef _tAb_H_
#define _tAb_H_

typedef struct ab tAb;

/// @brief Cria dinamicamente uma 
/// estrutuara tAb
/// @param caractere o caracctere do no 
/// @param frequencia quantas vezes o caractere 
/// foi lido
/// @param sae a subarvore da esquerda
/// @param sad a subarvore da direita
/// @return um ponteiro valiod para a arvore criada
tAb *CriaAb(unsigned char caractere, unsigned int frequencia, tAb *sae, tAb *sad);

/// @brief Libera a memoria utilizada
/// por uma estrutura tAb
/// @param abb a arvore que se deseja desalocar
void DesalocaaAb(tAb *ab);

/// @brief Une duas arvores
/// @param a1 uma arvore valida
/// @param a2 outra arvore valida
/// @return uma nova arvore com no 
/// contendo a soma da frequencia em a1 e a2
tAb *JoinAb(tAb *a1, tAb*a2);

/// @brief Obtem a frequencia contida numa Ab
/// @param ab uma arvore valida
/// @return a frequencia contida em AB
unsigned int getFreqAb(tAb *ab);

/// @brief Obtem o caractere contido numa Ab
/// @param ab uma arvore valida
/// @return o caractere contido em Ab
unsigned char getChAb(tAb *ab);

/// @brief Imprime uma arvore valida
/// @param ab ponteiro valido para uma 
/// variavel do tipo tAb
void ImprimeArvore(tAb *ab, int flag);

/// @brief Escreve uma arvore binaria em um arquivo binario dado
/// @param ab 
/// @param arq 
void WriteBinAb(tAb* ab, FILE* arq);

/// @brief Le uma arvore binaria de um arquivo binario dado
/// @param arq 
/// @return Retorna uma arvore lida e alocada dinamicamente
tAb* ReadBinAb(FILE* arq);

#endif