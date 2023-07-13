#include "estruturas.h"
#include "area.h"
#include "quickSort.h"

bool verificaInteiro(char * string){
    //Verifica se todos os valores contidos na string sao valores numericos
    int tamString = strlen(string);
    for(int i = 0; i < tamString; i++)
        if(!isdigit(string[i])) return false;
    return true;
}

bool verificaInputs(int argc, char const *argv[], InfoOrdenacao * infoOrdenacao){
    
    //Verifica se existe o arquivo PROVAO.TXT
    FILE * arqTemp = fopen("PROVAO.TXT", "r");
    if(arqTemp == NULL){
        printf("Não existe o arquivo PROVAO.TXT no diretório atual.\n");
        return false;
    }
    fclose(arqTemp);

    //Verificando o tamanho da entrada
    if(argc < 4 || argc > 5){ 
        printf("Os dados devem ser passados no terminal por: \n\t./executavel <metodo> <quantidade> <situação> [-P]\n");
        return false;
    }

    bool dadosCorretos = true;

    char tempString[50];
    strcpy(tempString, argv[1]);

    //Verificando se os dados sao inteiros e se podem ser convertidos
    if(!verificaInteiro(tempString) || atoi(argv[1]) <= 0 || atoi(argv[1]) >= 4){
        printf("O método deve ser passado como um inteiro.\n");
        printf("O método deve estar no intervalo [1, 3].\n");
        printf("\t1 - Ordenação balanceada por vários caminhos com método de ordenação interna de ED1\n");
        printf("\t2 - Ordenação balanceada por vários caminhos com substituição por seleção\n");
        printf("\t3 - QuickSort externo\n");
        dadosCorretos = false;
    }
    else{
        infoOrdenacao->metodo = atoi(argv[1]);
    }

    //Verificado se o numero de itens para ordenar esta correto
    strcpy(tempString, argv[2]);
    if(!verificaInteiro(tempString) || atoi(argv[2]) < 0 || atoi(argv[2]) > 471.705){
        printf("O número de itens a ser ordenado deve ser igual a 100, 1.000, 10.000, 100.000 ou 471.705");
        dadosCorretos = false;
    }
    int qtd = atoi(argv[2]);
    if(qtd != 100 && qtd != 1000 && qtd != 10000 && qtd != 100000 && qtd != 471705){
        printf("O número de itens a ser ordenado deve ser igual a 100, 1.000, 10.000, 100.000 ou 471.705");
        dadosCorretos = false;
    }
    else
        infoOrdenacao->quantidade = qtd;

    //Verifica se o tipo de ordenação esta correto
    strcpy(tempString, argv[3]);
    if(!verificaInteiro(tempString) || atoi(argv[3]) <= 0 || atoi(argv[3]) >= 4){
        printf("A situação deve ser passado como um inteiro que está no intervalo [1, 3].\n");
        printf("\t1 - Arquivo ordenado ascendentemente pelas notas\n");
        printf("\t2 - Arquivo ordenado descendentemente pelas notas\n");
        printf("\t3 - Arquivo desordenado aleatoriamente pelas notas\n");
        dadosCorretos = false;
    }
    else{
        infoOrdenacao->situacao = atoi(argv[3]);
    }

    return dadosCorretos;
}

int main(int argc, char const *argv[]){

    InfoOrdenacao infoOrdenacao;

    verificaInputs(argc, argv, &infoOrdenacao);

    geraBinario();

    return 0;
}