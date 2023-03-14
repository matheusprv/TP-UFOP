#include "indiceInvertido.h"
#include <time.h>

int main() {

    clock_t start, end;
    double execution_time;
    start = clock();

    IndiceInvertido indiceInvertido;
    int nDocumentos;

    inicia(indiceInvertido);
    leEntrada(indiceInvertido, &nDocumentos);
    leOpcao(indiceInvertido, nDocumentos);


    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printColisoes();
    printf("Tempo de execução do programa: %lfs.\n", execution_time);

    return 0;
}
