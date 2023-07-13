#ifndef AREA_H
#define AREA_H

#include "estruturas.h"

#define TAMAREA  20

typedef struct TipoArea{
    TipoRegistro area [TAMAREA];
    int n;
}TipoArea;

TipoArea inicializaArea();

void InsereItem(TipoRegistro UltLido, TipoArea *Area);

int ObterNumCelOcupadas(TipoArea * area);

void RetiraUltimo(TipoArea * area, TipoRegistro * R);

#endif