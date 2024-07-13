#include <stdio.h>
#include <stdlib.h>
#include "tAb.h"
#include "utils.h"

tAb* aumentaarv(tAb*a){
    if(a)printf("eitapreula");
}

struct ab{
    tAb *sad;
    tAb *sae;
    unsigned char ch;
    unsigned int freq;
};

static int ehFolha(tAb *a){
    if(a){
        return(a->sad == NULL && a->sae == NULL);
    }
    return 0;
}

static int maior(int a, int b){
    return (a > b) ? a : b;
}


tAb *CriaAb(unsigned char caractere, unsigned int frequencia, tAb *sae, tAb *sad){
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
    DesalocaaAb(abb->sae);
    DesalocaaAb(abb->sad);
    free(abb);
}

tAb *JoinAb(tAb *a1, tAb*a2){
    if(!a1 || !a2) TratarStructNula("join", "ab");

    //como a lista estara ordenada, 
    //essa criacao assume a1 < a2
    tAb *nova = CriaAb('\0', (a1->freq + a2->freq), a1, a2);

    return nova;
}

unsigned int getFreqAb(tAb *ab){
    if(!ab)TratarStructNula("getFreq", "ab");
    return ab->freq; 
}

unsigned char getChAb(tAb *ab){
    if(!ab)TratarStructNula("getCh", "ab");
    return ab->ch; 
}

void ImprimeArvore(tAb *ab, int flag){
    if(!ab) return;
    if(ehFolha(ab)){
        printf("%c\n", ab->ch);
        return;
    }
    ImprimeArvore(ab->sae, 1);
    ImprimeArvore(ab->sad, 0);
    printf("%d\n", flag);

}