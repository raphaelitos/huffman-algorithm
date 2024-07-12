#include <stdio.h>
#include <stdlib.h>
#include "tAb.h"
#include "utils.h"

struct ab{
    tAb *sad;
    tAb *sae;
    unsigned char ch;
    int freq;
};

tAb *CriaAb(unsigned char caractere, int frequencia, tAb *sae, tAb *sad){
    tAb *nova = (tAb*)calloc(1, sizeof(tAb));
    if(!nova)TratarFalhaAlocacao("arvore binaria");
    
    nova->ch = caractere;
    nova->freq = frequencia;
    nova->sad = sad;
    nova->sae = sae;
    
    return nova;
}

void DesalocaaAb(tAb *abb){
    if(!abb) return;
    desalocaaAbb(abb->sae);
    desalocaaAbb(abb->sad);
    free(abb);
}

tAb *JoinAb(tAb *a1, tAb*a2){
    if(!a1 || !a2) TratarStructNula("join", "ab");

    //como a lista estara ordenada, 
    //essa criacao assume a1 < a2
    tAb *nova = CriaAb('\0', (a1->freq + a2->freq), a1, a2);

    return nova;
}

int getFreqAb(tAb *ab){
    if(!ab)TratarStructNula("getFreq", "ab");
    return ab->freq; 
}

unsigned char getChAb(tAb *ab){
    if(!ab)TratarStructNula("getCh", "ab");
    return ab->ch; 
}