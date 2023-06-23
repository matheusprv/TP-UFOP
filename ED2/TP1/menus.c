#include "menus.h"

//Verifica se todas as entradas sao validas, se estao nos intervalos determinados e se o metodo pode utilizar determinada ordenacao de arquivo
bool verificaInputsValidos(int metodo, int quantidade, int situacao){
    bool dadosValidos = true;

    //Verifica se o metodo escolheu e valido
    if(metodo > 4 || metodo < 1){
        printErr("O método deve estar entre 1 e 4.\n");
        printf("\t1 - Acesso sequencial indexado;\n");
        printf("\t2 - Árvore binária de pesquisa;\n");
        printf("\t3 - Árvore B;\n");
        printf("\t4 - Árvore B*\n");

        dadosValidos = false;
    }

    //Verifica se a quantidade de itens nos arquivos sao validas
    if(quantidade != 100 && quantidade != 1000 && quantidade != 10000 && quantidade != 100000 && quantidade != 1000000) {
        printErr(("Quantidade de dados inválidas.\n"));
        printf("\tAs quantidades podem ser: 100, 1000, 10000, 100000 ou 1000000\n");
        dadosValidos = false;
    }

    //Verifica se a ordenacao do arquivo e valida
    if(situacao > 3 || situacao < 1){
        printErr("A situação deve estar entre 1 e 3.\n");
        printf("\t1 - Crescente;\n");
        printf("\t2 - Decrescente;\n");
        printf("\t3 - Aleatório\n");

        dadosValidos = false;
    }
    
    //Verifica se esta utilizando o acesso sequencial indexado com dados aleatorios
    if(metodo == 1 && situacao == 3){
        printWarning("O método de acesso sequencial indexado não pode utilizar dados aleatórios.\n");
        dadosValidos = false;
    }

    return dadosValidos;
}

//Retorna uma string com a ordenacao do arquivo
char * verificaSituacao(int situacao){
    if(situacao == 1) return "-crescente.bin";
    else if (situacao == 2) return "-decrescente.bin";
    else return "-aleatorio.bin";
}

//A partir do metodo e ordenacao do arquivo escolhido pelo usuario, gera o nome a ser utilizado na abertura do arquivo
char * geraNomeArquivo(char * quantidade, int situacao, char * nomeArquivo){
    strcpy(nomeArquivo, "Arquivos/");
    char * nome = strcat(quantidade, verificaSituacao(situacao));

    return strcat(nomeArquivo, nome);
}

//Converte uma chave de String para um valor Long
long converteChave(char * chaveStr){
    char * resto;
    int base = 10;
    long chave = strtol(chaveStr, &resto, base);
    
    return chave;
}

//Executa o metodo especificado pelo usuario
bool selecionaMetodo(int metodo, long chave, char * nomeArquivo, int quantidade, Resultados * resultado){

    if(metodo == 1)
        return acessoIndexado(nomeArquivo, resultado);

    else if(metodo == 2)
        return arvore_binaria_de_pesquisa(nomeArquivo, resultado);

     else if(metodo == 3)
         return arvore_b(nomeArquivo, quantidade, resultado);
        
    else
        return arvore_b_estrela(chave, nomeArquivo, quantidade, resultado);
   
}

//Imprime todos os resultados que foram obtidos a partir da pesquisa realizada
void imprimeResultados(Resultados * resultado){
    if(resultado->resultadoPesquisa){
        printSuccess("Resultado encontrado\n");

        if(resultado->metodo != 4){
            printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",
            resultado->pesquisar.Chave, resultado->pesquisar.dado1, resultado->pesquisar.dado2, resultado->pesquisar.dado3);
        }
            
        else {
            printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n", 
            resultado->pesquisarEstrela.Chave, resultado->pesquisarEstrela.dado1, resultado->pesquisarEstrela.dado2, resultado->pesquisarEstrela.dado3);
        }
    }
    else printErr("Resultado não encontrado\n");


    double tempo_execucao = ((double)(resultado->horario_fim - resultado->horario_inicio))/CLOCKS_PER_SEC;
    printf("Tempo de execução: %lf s\n", tempo_execucao);
}
