#include "area.h"
#include "estruturas.h"

TipoArea inicializaArea(){
    TipoArea area;
    area.n = -1;
    return area;
}

void InsereItem(TipoRegistro UltLido, TipoArea *Area){
    Area -> area[ Area->n + 1] = UltLido;
    Area -> n += 1;
}

int ObterNumCelOcupadas(TipoArea * area){
    return  area->n;
}

void RetiraUltimo(TipoArea * area, TipoRegistro * R){
    //Procurando o item no vetor para remover
    int i;
    for(i = 0; i < area->n; i++)
        if(area->area[i].Chave == R->Chave) break;

    //Puxando todos os itens uma posicao para tras a partir do item
    for(; i < area->n - 1; i++)
        area->area[i] = area->area[i+1];

    area->n -= 1;

}