#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void TratarStructNula(const char *nomeFuncao, const char *nomeStruct){
	printf("%s nula na funcao %s!\n", nomeStruct, nomeFuncao);
	exit(EXIT_FAILURE);
}

void TratarFalhaAlocacao(const char *nomeStruct){
	printf("Falha na criacao de %s", nomeStruct);
	exit(EXIT_FAILURE);
}

int EhMesmoTermo(char *str1, char*str2){
	if(!str1 || !str2) TratarStructNula("ehmesmotermo", "char*");
	return !strcmp(str1, str2);
}