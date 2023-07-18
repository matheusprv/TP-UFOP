// #include "ordenacao.h"
// #include <stdlib.h>
// #include <stdio.h>
// // #include <math.h>

// // Manter como especificado
// void desalocaVetor(Time **vetor)
// {
//     free(*vetor);
// }

// // implemente sua funcao de ordenacao aqui, que deve invocar a funcao compare
// void ordenacao(Time *vetor, int n)
// {
//     heapBuild(vetor, n);
//     //calculaRazao(vetor, n);
//     Time aux;
//     while (n > 1)
//     {
//         // copiaTime(&aux, &vetor[n - 1]);
//         // copiaTime(&vetor[n - 1], &vetor[0]);
//         // copiaTime(&vetor[0], &aux);
//         aux = vetor[n - 1];
//         vetor[n - 1] = vetor[0];
//         vetor[0] = aux;

//         n--;

//         heapReBuild(vetor, 0, n - 1);
//     }
// }

// void calculaRazao(Time *times, int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         if (times[i].pontosSofridos == 0)
//         {
//             times[i].razao = times[i].pontosFeitos;
//         }
//         else
//         {
//             times[i].razao = (float)times[i].pontosFeitos / times[i].pontosSofridos;
//         }
//     }
// }

// // compara dois elementos do vetor de times, indicado se o metodo de ordenacao deve troca-los de lugar ou nao
// int compare(TipoRegistro reg1, TipoRegistro reg2)
// {
//     if(reg1.nota < reg2.nota)
//     {
//         return 1;
//     }
//     return 0;
// }

// void heapBuild(TipoRegistro *regs, int n)
// {
//     int esq = (n / 2) - 1;
//     while (esq >= 0)
//     {
//         heapReBuild(regs, esq, n - 1);
//         esq--;
//     }
// }

// void heapReBuild(TipoRegistro *regs, int esq, int dir)
// {
//     int i = esq;
//     int j = i * 2 + 1;
//     TipoRegistro aux = regs[i];

//     while (j <= dir)
//     {
//         if (j < dir && (compare(regs[j], regs[j + 1]))) // Compara  os irmãos
//         {
//             j++; // Caso o irmão j + 1 tenha mais prioridade j passa a ser a posição dele
//         }

//         if (compare(aux, regs[j])) // Compara o irmão com mais prioridade com o pai
//         {
//             break; // Caso o pai tenha mais prioridade, sai fora do loop
//         }

//         copiaTime(&regs[i], &regs[j]); // Caso o pai esteja na posição errada, troca com o filho de maior prioridade
//         //times[i] = times[j];
//         i = j;
//         j = i * 2 + 1;
//     } 
//     copiaTime(&regs[i], &regs);
//     regs[i] = aux;
// }

// void copiaTime(TipoRegistro *reg1, TipoRegistro *reg2)
// {
//     reg1->Chave = reg2->Chave;
//     reg1->nota = reg2->nota;
//     reg1->estado = reg2->estado;
//     reg1->cidade = reg2->cidade;
//     reg1->curso = reg2->curso;
// }

