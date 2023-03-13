#include "indiceInvertido.h"

int main() {
    IndiceInvertido indiceInvertido;
    int nDocumentos;

    inicia(indiceInvertido);

    leEntrada(indiceInvertido, &nDocumentos);

    leOpcao(indiceInvertido, nDocumentos);

    return 0;
}
