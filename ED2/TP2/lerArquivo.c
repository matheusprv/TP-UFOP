#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

/*
Id: 1 a 8
Nota: 10 a 14
Estado: 16 e 17
Cidade: 19 a 68
curso: 70 a 99 
*/

int main(int argc, char const *argv[])
{
    FILE *arq = fopen("PROVAO.TXT", "r");
    if(arq == NULL){
        printf("Error: Cannot open file\n"); return 0;
    }

    int numAlunos = atoi(argv[1]);
    
    Aluno *alunos = (Aluno*) malloc (numAlunos * sizeof(Aluno));

    for (int i = 0; i < numAlunos; i++){
        fscanf(arq, "%d %f", &)
        fgets(alunos[i].estado, 10)

        fscanf(arq, "%d %f %2s %50s %30s\n", &alunos[i].id, &alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
    }
    
    for (int i = 0; i < numAlunos; i++)
    {
        printf("%d %f %s %s %s\n", alunos[i].id, alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
    }
    
    free(alunos);
    return 0;
}
