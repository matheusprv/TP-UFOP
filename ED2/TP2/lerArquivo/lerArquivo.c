#include <stdio.h>
#include <stdlib.h>
#include "../estruturas.h"

int main(){
    int qtdAlunos = 471705;
    //FILE *arq = fopen("../PROVAO_ALEATORIO.bin", "rb");
    FILE *arq = fopen("../QuickSort-crescente-100.bin", "rb");

    TipoRegistro * alunos = malloc(qtdAlunos * sizeof(TipoRegistro));

    fread(alunos, sizeof(TipoRegistro), qtdAlunos, arq);

    for(int i = 0; i < 100; i++){
        printf("%d %lf %s %s %s\n", alunos[i].Chave, alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
    }
    
    free(alunos);
    fclose(arq);
}