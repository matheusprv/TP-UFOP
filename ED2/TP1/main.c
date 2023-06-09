#include "acesso_indexado.h"
#include "estruturas.h"
#include "abp.h"

/*
    *metodo
    1 - Acesso sequencial indexado
    2 - Árvore binária de pesquisa
    3 - Árvore B
    4 - Árvore B*

    *Situacao
    1 - Crescente
    2 - Descrescente
    3 - Aleatorio
*/

#define END "\x1b[0m"
#define RED_COLOR "\x1b[31m"

void selecionaMetodo(int argc, char * argv[]){

    int metodo = atoi(argv[2]);
    int quantidade = atoi(argv[3]);
    int situacao = atoi(argv[4]);
    TipoChave chave = atoi(argv[5]);
    //int p = (argc == 7) ? atoi(argv[6]) : 0;

    printf("Metodo: %d, Situação: %d\n", metodo, situacao);
    
    if(metodo == 1 && situacao == 3){
        printf(RED_COLOR "Não é possível utilizar o Acesso Sequencial Indexado com o arquivo desornado aleatoriamente.\n" END);
        return;
    }
    
    char * nomeArquivo = strcat(quantidade, "-arquivo-");

    if(situacao == 1) nomeArquivo = strcat(nomeArquivo, "crescente.bin");
    else if(situacao == 2) nomeArquivo = strcat(nomeArquivo, "decrescente.bin");
    else if(situacao == 3) nomeArquivo = strcat(nomeArquivo, "aleatorio.bin");
    else{
        printf(RED_COLOR "Situação de arquivo inválida.\n" END);
        return;
    }
    

    if(metodo == 1) acessoIndexado(chave, nomeArquivo);
    else if (metodo == 2){
        constroiArvore(nomeArquivo);

        TipoRegistro x;
        x.Chave = chave;
        FILE *arq = fopen("abp.bin", "rb");

        if(pequisarAbp(arq, &x))
            printf("Registro encontrado\n");

        fclose(arq);
        remove("abp.bin");
    }
    else if(metodo == 3){

    }
    else if(metodo == 4){

    }
    else{
        printf(RED_COLOR "Método de pesquisa inválido.\n" END);
        return;
    }
    

}

int main(int argc, char * argv[]){

    selecionaMetodo(argc, argv);

    return 0;
}
