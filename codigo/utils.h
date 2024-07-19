#ifndef UTILS_H_
#define UTILS_H_

#define TAM_ASCII 256
#define ESQUERDA '0'
#define DIREITA '1'

/**
 * Encerra o programa apos avisar a funcao onde isso
 * ocorreu e de qual estrutura se trata
*/
void TratarStructNula(const char *nomeFuncao, const char *nomeStruct);

/**
 * Encerra o programa apos indicar o tipo 
 * de dado que iria ser alocado
*/
void TratarFalhaAlocacao(const char *nomeStruct);

/**
 * Compara dois termos validos e diz se sao iguais.
*/
int EhMesmoTermo(char *str1, char*str2);

#endif