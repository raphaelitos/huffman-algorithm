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

tAb *criaAb(){
    tAb *nova = NULL;
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