#include "ordenacao.h"

//HeapSort:

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

//QuickSort Interno:

void trocarPosicao(TipoRegistro* registros, int * i, int * j){
    TipoRegistro auxiliar;

    auxiliar = registros[*i];
    registros[*i] = registros[*j];
    registros[*j] = auxiliar;
    *i += 1;
    *j -= 1;

}

void quicksort_interno(TipoRegistro * registros, int inicio, int fim){
    int i, j;
    TipoRegistro pivo; 

    i = inicio;
    j = fim;
    pivo = registros[(inicio + fim) / 2];

    while (i <= j){
        while (registros[i].nota < pivo.nota && i < fim)
            i++;
        
        while (registros[j].nota > pivo.nota && j > inicio)
            j--;

        if (i <= j)
            trocarPosicao(registros, &i, &j);
    }

    if (j > inicio)
        quicksort_interno(registros, inicio, j);

    if (i < fim)
        quicksort_interno(registros, i, fim);
}