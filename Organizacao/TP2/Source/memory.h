#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"

typedef struct {
    int words[WORDS_SIZE];
} MemoryBlock;

typedef struct {
    MemoryBlock* blocks;
    int size;
} RAM;

typedef struct {
    MemoryBlock block;
    int tag; /* Address of the block in memory RAM */
    bool updated;
    int cost;
    int cacheHit;
    
    #if defined LFU
        int contador;
    #endif

} Line;

#ifdef LRU
    typedef struct{
        int pos;
    }Item;

    typedef struct celula{
        struct celula * prox;
        Item item;
    }Celula;

    typedef struct {
        Celula * cabeca;
        Celula * fim;
    }Lista;
    
    void iniciaLista(Lista * lista);
    void insereInicio(Lista * lista, Item item);
    void levaParaComeco(Lista * lista, Item item);
    void removeFinal(Lista * lista);
    void desalocaLista(Lista * lista);

#endif

typedef struct {
    Line* lines;
    int size;

    #ifdef LRU
        Lista * lista;
    #endif

} Cache;

void startCache(Cache*, int);
void stopCache(Cache*);

void startRAM(RAM*, int);
void stopRAM(RAM*);

#endif // !MEMORY_H