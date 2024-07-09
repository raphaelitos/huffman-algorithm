#include <stdio.h>
#include <stdlib.h>
#include "tAb.h"
#include "utils.h"

struct ab{
    tAb *sad;
    tAb *sae;
    char ch;
    int freq;
};

tAb *criaAb(char caractere, int frequencia, tAb *sae, tAb *sad){
    tAb *nova = (tAb*)calloc(1, sizeof(tAb));
    if(!nova)TratarFalhaAlocacao("arvore binaria");
    
    nova->ch = caractere;
    nova->freq = frequencia;
    nova->sad = sad;
    nova->sae = sae;
    
    return nova;
}

void desalocaaAb(tAb *abb){
    if(!abb) return;
    desalocaaAbb(abb->sae);
    desalocaaAbb(abb->sad);
    free(abb);
}

int getFreqAb(tAb *ab){
    if(!ab)TratarStructNula("getFreq", "ab");
    return ab->freq; 
}

char getChAb(tAb *ab){
    if(!ab)TratarStructNula("getCh", "ab");
    return ab->ch; 
}