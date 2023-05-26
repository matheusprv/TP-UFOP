#include <time.h>
#include "estruturas.h"

void reverseArray(TipoRegistro arr[], int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        // Swap elements at start and end indices
        TipoRegistro temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move the indices towards the center
        start++;
        end--;
    }
}

void shuffleArray(TipoRegistro arr[], int size) {
    srand(time(NULL));

    for (int i = size - 1; i > 0; i--) {
        // Generate a random index between 0 and i (inclusive)
        int j = rand() % (i + 1);

        // Swap elements at index i and j
        TipoRegistro temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


int main(){

    srand(time(NULL));

    char * caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$&*";
    //int tamString = strlen(caracteres);

    int numArquivos = 5;
    int qtdItens[5] = {100, 1000, 10000, 100000, 1000000};


    TipoRegistro * registros = (TipoRegistro *) malloc(1000000 * sizeof(TipoRegistro));

    //Gerando valores aleatorios para os registros
    for(int i = 0; i < 1000000; i++){
        registros[i].Chave = i+1;
        registros[i].dado1 = rand();
        strcpy(registros[i].dado2, "VALOR TESTE");
        strcpy(registros[i].dado3, "VALOR TESTE");

        /*int numero_de_caracteres = (rand() % 1000)+1;
        int caracter_atual;
        int j;

        //Gerando um tamanho de string e valores aleatórios para a string dado2
        for(j = 0; j < numero_de_caracteres; j++){
            caracter_atual = rand() % tamString;
            registros[i].dado2[j] = caracteres[caracter_atual];
        }
        registros[i].dado2[j] = '\0';

        //Gerando um tamanho de string e valores aleatórios para a string dado3
        numero_de_caracteres = (rand() % 5000) + 1;
        for(j = 0; j < numero_de_caracteres; j++){
            caracter_atual = rand() % tamString;
            registros[i].dado3[j] = caracteres[caracter_atual];
        }
        registros[i].dado3[j] = '\0';*/
    }

    printf("Valores aleatórios gerados.\n");

    //Salvando os dados em ordem crescente
    FILE * arquivo = fopen("100-arquivo_crescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[0], arquivo);
    fclose(arquivo);

    /*arquivo = fopen("1000-arquivo_crescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[1], arquivo);
    fclose(arquivo);

    arquivo = fopen("10000-arquivo_crescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[2], arquivo);
    fclose(arquivo);

    arquivo = fopen("100000-arquivo_crescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[3], arquivo);
    fclose(arquivo);

    arquivo = fopen("1000000-arquivo_crescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[4], arquivo);
    fclose(arquivo);

    printf("Arquivo crescente salvo.\n");*/




    //Salvando os dados em ordem decrescente
    reverseArray(registros, 1000000);
    arquivo = fopen("100-arquivo_decrescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[0], arquivo);
    fclose(arquivo);

    /*arquivo = fopen("1000-arquivo_decrescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[1], arquivo);
    fclose(arquivo);

    arquivo = fopen("10000-arquivo_decrescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[2], arquivo);
    fclose(arquivo);

    arquivo = fopen("100000-arquivo_decrescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[3], arquivo);
    fclose(arquivo);

    arquivo = fopen("1000000-arquivo_decrescente.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[4], arquivo);
    fclose(arquivo);
    printf("Arquivo decrescente salvo.\n");*/

    //Vetor em ordem aleatório
    shuffleArray(registros, 1000000);
    arquivo = fopen("100-arquivo_aleatorio.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[0], arquivo);
    fclose(arquivo);

    /*arquivo = fopen("1000-arquivo_aleatorio.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[1], arquivo);
    fclose(arquivo);

    arquivo = fopen("10000-arquivo_aleatorio.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[2], arquivo);
    fclose(arquivo);

    arquivo = fopen("100000-arquivo_aleatorio.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[3], arquivo);
    fclose(arquivo);

    arquivo = fopen("1000000-arquivo_aleatorio.bin", "wb");
    fwrite(registros, sizeof(TipoRegistro), qtdItens[4], arquivo);
    fclose(arquivo);
    printf("Arquivo aleatório salvo.\n");*/

    free(registros);

    return 0;
}