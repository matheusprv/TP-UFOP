#include "menus.h"
#include <time.h>

int main(int argc, char * argv[]){

    if(argc < 5){
        printf(RED("Quantidade de parâmetros inválida\n"));
        printf("\t./nome_executavel <metodo> <quantidade_de_itens> <situacao> <chave> [-P]");
        return 0;
    }

    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    char chaveArg[10];
    strcpy(chaveArg, argv[4]);
    //int p = argc == 6 ? atoi(argv[5]) : -1;  
    if(!verificaInputsValidos(metodo, quantidade, situacao)) return 0;


    char nomeArquivo [100];
    geraNomeArquivo(argv[2], situacao, nomeArquivo);


    if(strcmp(chaveArg, "-a") != 0){

        long chave = converteChave(chaveArg);

        Resultados resultado;
        resultado.metodo = metodo;
        resultado.pesquisar.Chave = chave;
        resultado.pesquisarEstrela.Chave = chave;

        resultado.preProcessamento.transferencias = 0;
        resultado.preProcessamento.comparacoes = 0;

        resultado.pesquisa.transferencias = 0;
        resultado.pesquisa.comparacoes = 0;

        resultado.resultadoPesquisa = selecionaMetodo(metodo, chave, nomeArquivo, quantidade, &resultado);

        imprimeResultados(&resultado);

    }
    else{

        Resultados resultados [10];
        srand(time(NULL));

        gerarNumerosAleatorios(nomeArquivo, quantidade, resultados);

        //Pesquisa a chave de acordo com o metodo
        for(int i = 0; i < 10; i++){
            resultados[i].preProcessamento.transferencias = 0;
            resultados[i].preProcessamento.comparacoes = 0;

            resultados[i].pesquisa.transferencias = 0;
            resultados[i].pesquisa.comparacoes = 0;

            resultados[i].metodo = metodo;
            resultados[i].resultadoPesquisa = selecionaMetodo(metodo, resultados[i].pesquisar.Chave, nomeArquivo, quantidade, &resultados[i]);
            imprimeResultados(&(resultados[i]));
        }

        calculaMediaExecucoes(resultados);

    }

    return 0;
}