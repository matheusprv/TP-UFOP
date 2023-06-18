#include "menus.h"

bool verificaInputsValidos(int metodo, int quantidade, int situacao){
    bool dadosValidos = true;

    if(metodo > 4 || metodo < 1){
        printErr("O método deve estar entre 1 e 4.\n");
        printf("\t1 - Acesso sequencial indexado;\n");
        printf("\t2 - Árvore binária de pesquisa;\n");
        printf("\t3 - Árvore B;\n");
        printf("\t4 - Árvore B*\n");

        dadosValidos = false;
    }

    if(quantidade != 100 && quantidade != 1000 && quantidade != 10000 && quantidade != 100000 && quantidade != 1000000) {
        printErr(("Quantidade de dados inválidas.\n"));
        printf("\tAs quantidades podem ser: 100, 1000, 10000, 100000 ou 1000000\n");
        dadosValidos = false;
    }

    if(situacao > 3 || situacao < 1){
        printErr("A situação deve estar entre 1 e 3.\n");
        printf("\t1 - Crescente;\n");
        printf("\t2 - Decrescente;\n");
        printf("\t3 - Aleatório\n");

        dadosValidos = false;
    }
    
    if(metodo == 1 && situacao == 3){
        printWarning("O método de acesso sequencial indexado não pode utilizar dados aleatórios.\n");
        dadosValidos = false;
    }

    return dadosValidos;
}

char * verificaSituacao(int situacao){
    if(situacao == 1) return "-crescente.bin";
    else if (situacao == 2) return "-decrescente.bin";
    else return "-aleatorio.bin";
}

char * geraNomeArquivo(char * quantidade, int situacao, char * nomeArquivo){
    strcpy(nomeArquivo, "Arquivos/");
    char * nome = strcat(quantidade, verificaSituacao(situacao));

    return strcat(nomeArquivo, nome);
}

long converteChave(char * chaveStr){
    char * resto;
    int base = 10;
    long chave = strtol(chaveStr, &resto, base);
    
    return chave;
}

void selecionaMetodo(int metodo, long chave, char * nomeArquivo, int quantidade){
    if(metodo == 1)
        acessoIndexado(chave, nomeArquivo);

    else if(metodo == 2)
        arvore_binaria_de_pesquisa(chave, nomeArquivo);

     else if(metodo == 3)
         arvore_b(chave, nomeArquivo, quantidade);
    
}
