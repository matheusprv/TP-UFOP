#include "indiceInvertido.h"

void inicia(IndiceInvertido indiceInv){
    int i;

    for (i = 0; i < M ; i ++) {
        memcpy ( indiceInv[i]. chave , VAZIO , N);
    }
}

bool insereDocumento(IndiceInvertido indiceInv, Item x, NomeDocumento documento, int p){
    if (TDicionario_Pesquisa (indiceInv, x.chave, p) >= 0)
        return 0;
    int j = 0;
    int ini = h (x. chave , p);

    while ( strcmp (indiceInv[( ini + j) % M ].chave , VAZIO) != 0 && j < M ) {
       j ++; 
    }
    if (j < M){
        indiceInv[(ini + j) % M] = x;
        return true;
    }
    return false;
}

int busca(IndiceInvertido indiceInv, Chave chave, int p){
    int j = 0;
    int ini = h(chave, p);

    while(strcmp(indiceInv[( ini + j) % M ].chave , VAZIO) != 0 && strcmp (indiceInv[( ini + j ) % M ].chave , chave) != 0 && j < M ){
        j++;
    }

    if(strcmp(indiceInv[(ini + j) % M].chave, chave) == 0){
        return (ini + j) % M;
    }
    return -1;
}

int consulta(IndiceInvertido indiceInv, Chave *chave, int n, NomeDocumento* documento){

}

void imprime(IndiceInvertido indiceInv){
    for(int i=0; i < indiceInv.n; i++){

    }
}

void sort(NomeDocumento* documento, int n){

}
