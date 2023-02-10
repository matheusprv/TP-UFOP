#include "memory.h"

void startRAM(RAM* ram, int size) {
    ram->blocks = (MemoryBlock*) malloc(sizeof(MemoryBlock) * size);
    ram->size = size;

    for (int i=0;i<size;i++) {
        for (int j=0;j<WORDS_SIZE;j++)
            ram->blocks[i].words[j] = rand() % 100;            
    }
}

void stopRAM(RAM *ram) {
    free(ram->blocks);
}


void startCache(Cache* cache, int size) {
    cache->lines = (Line*) malloc(sizeof(Line) * size);
    cache->size = size;

    for (int i=0;i<size;i++)
        cache->lines[i].tag = INVALID_ADD;
}

void stopCache(Cache *cache) {
    free(cache->lines);
}

#ifdef LRU
    void iniciaLista(Lista * lista){
        lista->cabeca = (Celula *)malloc(sizeof(Celula));
        if (lista->cabeca == NULL)
            exit(1);
        lista->fim = lista->cabeca;
        lista->cabeca->prox = NULL;
    }


    void insereInicio(Lista * lista, Item item){
        
        Celula * nova = (Celula*) malloc(sizeof(Celula));
        nova->item = item;
        nova->prox = lista->cabeca->prox;
        lista->cabeca->prox = nova;  

    }

    void levaParaComeco(Lista * lista, Item item){
        Celula *aux = lista->cabeca->prox;
        Celula *anterior = lista->cabeca;
        
        while(aux->item.pos != item.pos){
            aux = aux->prox;
            anterior = anterior->prox;
        }

        anterior->prox = aux->prox;
        
        aux->prox = lista->cabeca->prox;
        lista->cabeca->prox = aux;
    }


    void removeFinal(Lista * lista){
        Celula *aux = lista->cabeca;
        
        while(aux->prox->prox!=NULL)
            aux = aux->prox;

        free(aux->prox);

        aux->prox=NULL;
        lista->fim = aux;

    }

    void desalocaLista(Lista* lista){
        Celula * atual = lista->cabeca;
        Celula * prox = lista->cabeca->prox;
        
        while(prox != NULL){
            free(atual);
            atual = prox;
            prox = atual->prox;
        }
        free(atual);
    }

#endif