#include "area.h"
#include "estruturas.h"

TipoArea inicializaArea(){
    TipoArea area;
    area.n = 0;
    return area;
}

void InsereItem(TipoRegistro UltLido, TipoArea *Area){
    Area -> area[Area->n] = UltLido;
    Area -> n ++;
    ordenaArea(Area->area, 0, Area->n - 1);
}

int ObterNumCelOcupadas(TipoArea * area){
    return area->n;
}

void RetiraUltimo(TipoArea * area, TipoRegistro * R){
    *R = area->area[area->n-1];
    area->n --;
}

void RetiraPrimeiro(TipoArea * area, TipoRegistro * R){
    *R = area->area[0];

    for(int i = 0; i < area->n; i++)
        area->area[i] = area->area[i+1];

    area->n--;
}

void trocaPosicao(TipoRegistro* registros, int * i, int * j){
    TipoRegistro auxiliar;
    auxiliar = registros[*i];
    registros[*i] = registros[*j];
    registros[*j] = auxiliar;
    *i += 1;
    *j -= 1;
}

void ordenaArea(TipoRegistro * registros, int inicio, int fim){
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
            trocaPosicao(registros, &i, &j);
    }

    if (j > inicio)
        ordenaArea(registros, inicio, j);

    if (i < fim)
        ordenaArea(registros, i, fim);
}