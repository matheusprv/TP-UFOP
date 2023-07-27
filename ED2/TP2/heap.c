#include "heap.h"

int compare(const RegistroParaSubstituicao registro1, const RegistroParaSubstituicao registro2) {
    //retornos: 1 = devem  ser trocados, 0 = não devem ser trocados
    
    if(registro1.marcado == registro2.marcado)
        if(registro1.registros.nota > registro2.registros.nota)
            return 1;
        else
            return 0;

    else if(registro1.marcado && !registro2.marcado)
        return 1;

    //caso em que o primeiro nao é marcado, e o segundo é marcado
    return 0;
}


void heap_constroi(RegistroParaSubstituicao *v, int n){
    int esq = (n/2) - 1; //esq = primeiro no antes do no folha do heap

    while(esq >= 0){
        heap_refaz(v, esq, n-1);
        esq--;
    }
}

void heap_refaz(RegistroParaSubstituicao *v, int esq, int dir){
    int i = esq;
    int j = i * 2 + 1;
    RegistroParaSubstituicao aux = v[i];

    while (j <= dir){
        if (j < dir && !compare(v[j], v[j+1]))
            j += 1; //j recebe o outro filho de i
    
        if(compare(aux, v[j]))
            break;

        v[i] = v[j];
        i = j;
        j = i * 2 + 1;
    }

    v[i] = aux;    
}

void heap_sort(RegistroParaSubstituicao *v, int n){
    heap_constroi(v, n);

    RegistroParaSubstituicao aux;
    while (n > 1){
        aux = v[n-1];
        v[n-1] = v[0];
        v[0] = aux;
        n = n-1;

        heap_refaz(v, 0, n-1); //refaz o heap
    }
}