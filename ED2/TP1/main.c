#include "menus.h"

int main(int argc, char * argv[]){

    if(argc < 5){
        printf(RED("Quantidade de parâmetros inválida\n"));
        printf("\t./nome_executavel <metodo> <quantidade_de_itens> <situacao> <chave> [-P]");
        return 0;
    }

    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    long chave = converteChave(argv[4]);
    //int p = argc == 6 ? atoi(argv[5]) : -1;

    if(!verificaInputsValidos(metodo, quantidade, situacao)) return 0;
    
    char nomeArquivo [100];
    geraNomeArquivo(argv[2], situacao, nomeArquivo);

    //clock_t comeco, fim;

    TipoRegistro pesquisar;
    TipoRegistroEstrela pesquisarEstrela;   

    bool resultado_pesquisa = selecionaMetodo(metodo, chave, nomeArquivo, quantidade, &pesquisar, &pesquisarEstrela);

    if(resultado_pesquisa){
        printSuccess("Resultado encontrado\n");

        if(metodo != 4) printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",pesquisar.Chave, pesquisar.dado1, pesquisar.dado2, pesquisar.dado3);
        else printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n", pesquisarEstrela.Chave, pesquisarEstrela.dado1, pesquisarEstrela.dado2, pesquisarEstrela.dado3);
    }
    else printErr("Resultado não encontrado\n");


    return 0;
}