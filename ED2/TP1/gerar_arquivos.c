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
    int tamString = strlen(caracteres);

    int qtdItens[5] = {100, 1000, 10000, 100000, 1000000};
    char qtdItens_string[5][8] = {"100", "1000", "10000", "100000", "1000000"};

    TipoRegistro * registros = (TipoRegistro *) malloc(1000000 * sizeof(TipoRegistro));

    //Gerando valores aleatorios para os registros
    for(int i = 0; i < 1000000; i++){
        registros[i].Chave = i+1;
        registros[i].dado1 = rand();
        //strcpy(registros[i].dado2, "VALOR TESTE 1");
        //strcpy(registros[i].dado3, "VALOR TESTE 2");

        int numero_de_caracteres = (rand() % 100)+1;
        int caracter_atual;
        int j;

        //Gerando um tamanho de string e valores aleatórios para a string dado2
        for(j = 0; j < numero_de_caracteres; j++){
            caracter_atual = rand() % tamString;
            registros[i].dado2[j] = caracteres[caracter_atual];
        }
        registros[i].dado2[j] = '\0';

        //Gerando um tamanho de string e valores aleatórios para a string dado3
        numero_de_caracteres = (rand() % 500) + 1;
        for(j = 0; j < numero_de_caracteres; j++){
            caracter_atual = rand() % tamString;
            registros[i].dado3[j] = caracteres[caracter_atual];
        }
        registros[i].dado3[j] = '\0';
    }
    printf("Valores aleatórios gerados.\n");

    int gerar_quantos_tipos = 4;

    //Salvando os dados em ordem crescente
    
    for(int i = 0; i <=gerar_quantos_tipos; i++){
        char fileName[51];
        strcpy(fileName, qtdItens_string[i]);
        strcat(fileName, "-arquivo-crescente.bin");
        FILE * arquivo = fopen(fileName,"wb");
        fwrite(registros, sizeof(TipoRegistro), qtdItens[i], arquivo);
        fclose(arquivo);
    }
    printf("Arquivo crescente salvo.\n");


    //Salvando os dados em ordem decrescente
    reverseArray(registros, 1000000);
    for(int i = 0; i <=gerar_quantos_tipos; i++){
        char fileName[51];
        strcpy(fileName, qtdItens_string[i]);
        strcat(fileName, "-arquivo-decrescente.bin");
        FILE * arquivo = fopen( fileName ,"wb");
        fwrite(registros, sizeof(TipoRegistro), qtdItens[i], arquivo);
        fclose(arquivo);
    }
    printf("Arquivo decrescente salvo.\n");



    //Salvando em ordem aleatório
    shuffleArray(registros, 1000000);
    for(int i = 0; i <= gerar_quantos_tipos; i++){
        char fileName[51];
        strcpy(fileName, qtdItens_string[i]);
        strcat(fileName, "-arquivo-aleatorio.bin");
        FILE * arquivo = fopen(fileName ,"wb");
        fwrite(registros, sizeof(TipoRegistro), qtdItens[i], arquivo);
        fclose(arquivo);
    }
    printf("Arquivo aleatório salvo.\n");

    free(registros);

    return 0;
}