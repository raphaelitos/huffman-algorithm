#include <stdio.h>
#include <stdlib.h>
#include "tAb.h"
#include "utils.h"

struct ab{
    tAb *sad;
    tAb *sae;
    unsigned char ch;
    unsigned int freq;
};

int ehFolha(tAb *a){
    if(a){
        return(a->sad == NULL && a->sae == NULL);
    }
    return 0;
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

tAb* GetSae(tAb* ab) {
    return ab->sae;
}

tAb* GetSad(tAb* ab) {
    return ab->sad;
}

tAb* CriaArvoreHuf(tLista* nos){
    if(!nos)TratarStructNula("CriaArvHuf", "lista");
    
    if(getSizeLista(nos) == 0) return NULL;

    if(getSizeLista(nos) == 1){
        return RetiraLista(nos);
    }

    tAb *a1 = RetiraLista(nos);
    tAb *a2 = RetiraLista(nos);
    tAb *nova = JoinAb(a1, a2);
    InsereLista(nos, nova);
    
    return CriaArvoreHuf(nos);
}

void DumpArvoreBitmap(tAb *ab, bitmap *bm){
    if(!ab || !bm) TratarStructNula("dumpArvBitmap", "ab ou bitmap");
    if(ehFolha(ab)){
        bitmapAppendLeastSignificantBit(bm, 1);
        bitmapAppendByte(bm, ab->ch);
        return;
    }
    else{
        bitmapAppendLeastSignificantBit(bm, 0);
    }
    DumpArvoreBitmap(ab->sae, bm);
    DumpArvoreBitmap(ab->sad, bm);
}

tAb *ReadArvoreBitmap(bitmap *bm, unsigned int *index) {
    if (!bm) TratarStructNula("ReadArvoreBitmap", "bitmap");

    if((*index) >= bitmapGetLength(bm)) return NULL;

    if (bitmapGetBit(bm, *index) == 1) {
        (*index)++;
        tAb *folha = CriaAb(bitmapGetByte(bm, *index), 0, NULL, NULL);
        (*index) += 8;
        return folha;
    }
    tAb *ab = CriaAb('\0', 0, NULL, NULL);
    (*index)++;
    ab->sae = ReadArvoreBitmap(bm, index);
    ab->sad = ReadArvoreBitmap(bm, index);

    return ab;
}
