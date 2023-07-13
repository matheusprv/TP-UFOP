// #include <stdio.h>
// #include <stdlib.h>
// #include "estruturas.h"

// int main(int argc, char const *argv[])
// {
//     FILE *arq = fopen("PROVAO.TXT", "r");
//     if(arq == NULL){
//         printf("Error: Cannot open file\n"); return 0;
//     }

//     int numAlunos = atoi(argv[1]);
//     TipoRegistro *alunos = (TipoRegistro*) malloc (numAlunos * sizeof(TipoRegistro));

//     for (int i = 0; i < numAlunos; i++){
//         fscanf(arq, "%d %lf", &alunos[i].Chave, &alunos[i].nota);
//         fgets(alunos[i].estado, 2, arq);
//         fgets(alunos[i].cidade, 50, arq);
//         fgets(alunos[i].curso, 30, arq);
//     }
    
//     for (int i = 0; i < numAlunos; i++){
//         printf("%-8d %.1f %2s %s %s\n", alunos[i].Chave, alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
//     }
    
//     free(alunos);
//     return 0;
// }
