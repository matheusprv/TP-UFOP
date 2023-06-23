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

    Resultados resultado;
    resultado.pesquisar.Chave = chave;
    resultado.pesquisarEstrela.Chave = chave;
    resultado.metodo = metodo;

    //Inicializando as variaveis estaticas
    transferenciasPreProcessamento();
    comparacoesPreProcessamento();
    transferenciasPesquisa();
    comparacoesPesquisa();
  
    resultado.resultadoPesquisa = selecionaMetodo(metodo, chave, nomeArquivo, quantidade, &resultado);

    imprimeResultados(&resultado);



    return 0;
}