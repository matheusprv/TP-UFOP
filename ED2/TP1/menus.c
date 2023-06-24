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
   
    return false;
}

//Imprime todos os resultados que foram obtidos a partir da pesquisa realizada
void imprimeResultados(Resultados * resultado){
    if(resultado->resultadoPesquisa){
        printSuccess("Resultado encontrado\n");

        /*if(resultado->metodo != 4){
            printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",
            resultado->pesquisar.Chave, resultado->pesquisar.dado1, resultado->pesquisar.dado2, resultado->pesquisar.dado3);
        }
            
        else {
            printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n", 
            resultado->pesquisarEstrela.Chave, resultado->pesquisarEstrela.dado1, resultado->pesquisarEstrela.dado2, resultado->pesquisarEstrela.dado3);
        }*/

        if(resultado->metodo != 4){
            printf("\tchave: %ld \n",
            resultado->pesquisar.Chave);
        }
            
        else {
            printf("\tchave: %ld \n", 
            resultado->pesquisarEstrela.Chave);
        }
    }
    else 
        printErr("Resultado não encontrado para a Chave\n");


    printf("===============\n");
    double tempoPreProcessamento = ((double)(resultado->tempoPreProcessamento[1] - resultado->tempoPreProcessamento[0]))/CLOCKS_PER_SEC;
    double tempoPesquisa = ((double)(resultado->tempoPesquisa[1] - resultado->tempoPesquisa[0]))/CLOCKS_PER_SEC;
    double tempoTotal = tempoPreProcessamento + tempoPesquisa; 
    printf("\tTempo de pré-processamento: %lf s\n", tempoPreProcessamento);
    printf("\tTempo de pesquisa: %.5lf s\n", tempoPesquisa);
    printf("\tTempo total: %.5lf s\n", tempoTotal);
    
    long int qtdTransferenciasPreProcessamento = resultado->preProcessamento.transferencias;
    long int qtdComparacoesPreProcessamento = resultado->preProcessamento.comparacoes;
    printf("===============\n");
    printf("\tNúmero de transferências do pré-processamento: %ld\n", qtdTransferenciasPreProcessamento);
    printf("\tNúmero de comparações do pré-processamento: %ld\n", qtdComparacoesPreProcessamento);

    long int qtdTransferenciasPesquisa = resultado->pesquisa.transferencias;
    long int qtdComparacoesPesquisa = resultado->pesquisa.comparacoes;
    printf("===============\n");
    printf("\tNúmero de transferências da pesquisa: %ld\n", qtdTransferenciasPesquisa);
    printf("\tNúmero de comparações da pesquisa: %ld\n", qtdComparacoesPesquisa);

    long int transferenciaTotal = qtdTransferenciasPesquisa + qtdTransferenciasPreProcessamento;
    long int comparacoesTotal = qtdComparacoesPesquisa + qtdComparacoesPreProcessamento;
    printf("===============\n");
    printf("\tNúmero de transferências total: %ld\n", transferenciaTotal);
    printf("\tNúmero de comparações total: %ld\n", comparacoesTotal);

}

//Verifica se ha uma chave repetida dentro de um vetor
bool verificaChaveRepetida(int posicao, int *posicoes, int tam){
    for (int i = 0; i < tam; i++)
        if(posicao == posicoes[i])
            return true;

    return false;
}

//Gera 10 numeros aleatorios para realizar a pesquisa automatizada
void gerarNumerosAleatorios(char * nomeArquivo, int quantidade, Resultados * resultados){

    int posicao[10];
    TipoRegistro reg;

    FILE * arq = fopen(nomeArquivo, "rb");
    int n = 0;
    //Gera as 10 chaves aleatorias para pesquisar
    for(int i = 0; i < 10; i++){

        int posRand = rand()%quantidade;

        if(verificaChaveRepetida(posRand, posicao, n)){
            while(verificaChaveRepetida(posRand, posicao, n)){
                posRand = rand()%quantidade;  
            }
        }
        posicao[i] = posRand;
        n++;
        
        //Lendo a chave e salvando no vetorde resultados
        fseek(arq, (posicao[i])*sizeof(TipoRegistro),SEEK_SET);
        fread(&reg, sizeof(TipoRegistro), 1, arq);
        resultados[i].pesquisar.Chave = reg.Chave;
        resultados[i].pesquisarEstrela.Chave = reg.Chave;

    }

    fclose(arq);

}

//Recebe um registro que salvara os resultados e realiza as pesquisas
void realizarPesquisa(Resultados * resultado, long chave, char * nomeArquivo, int quantidade){

    resultado->pesquisar.Chave = chave;
    resultado->pesquisarEstrela.Chave = chave;

    resultado->resultadoPesquisa = selecionaMetodo(resultado->metodo, chave, nomeArquivo, quantidade, resultado);

    imprimeResultados(resultado);

}

void calculaMediaExecucoes(Resultados *resultados){

    clock_t tempoPreProcessamentoTotal = 0;
    clock_t tempoPesquisaTotal = 0;
    int comparacoesTotal = 0;
    int transferenciasTotal = 0;

    for(int i = 0; i < 10; i++){
        tempoPreProcessamentoTotal += (double)((resultados[i].tempoPreProcessamento[1] - resultados[i].tempoPreProcessamento[0])/CLOCKS_PER_SEC);
        tempoPesquisaTotal += (double)((resultados[i].tempoPesquisa[1] - resultados[i].tempoPesquisa[0])/CLOCKS_PER_SEC);
        comparacoesTotal += resultados[i].pesquisa.comparacoes + resultados[i].preProcessamento.comparacoes;
        transferenciasTotal += resultados[i].pesquisa.comparacoes + resultados[i].preProcessamento.transferencias;
    }   

    printf("Tempo de execucao total no pre processamento de todas execucoes: %ld\n", tempoPreProcessamentoTotal); 
    printf("Tempo de execucao total na pesquisa de todas execucoes: %ld\n",  tempoPesquisaTotal);
    printf("Quantidade de comparacoes em todas execucoes: %d\n", comparacoesTotal);
    printf("Quantidade de transferencias em todas execucoes: %d\n", transferenciasTotal);
    
    

    //double tempo =((double)(resultado->tempoPesquisa[1] - resultado->tempoPesquisa[0]))/CLOCKS_PER_SEC;*/
}