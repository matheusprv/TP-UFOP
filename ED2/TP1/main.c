// !Conflito com as structs da arvore b estrea e as normais
//#include "acesso_indexado.h"
//#include "estruturas.h"
//#include "abp.h"
//#include "arvore_b.h"
#include "arvore_b_estrela.h"
#include <string.h>


/*
    !ARVORE B
    FILE * arq = fopen("Arquivos/100-arquivo-crescente.bin", "rb");

    TipoRegistro registros [100];
    fread(registros, 100, sizeof(TipoRegistro), arq);

    TipoApontador Arvore = NULL;

    for(int i = 0; i < 100; i++)
        Insere(registros[i], &Arvore);
    fclose(arq);


    TipoRegistro pesquisa;
    pesquisa.Chave = 1;
    if(pesquisa_arvore_b(&pesquisa, Arvore))
         printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",pesquisa.Chave, pesquisa.dado1, pesquisa.dado2, pesquisa.dado3);

    else
        printf("Não encontrou\n");
*/

int main(int argc, char * argv[]){

    FILE * arq = fopen("Arquivos/10000-arquivo-aleatorio.bin", "rb");

    TipoRegistro registros[10000];
    fread(registros, 10000, sizeof(TipoRegistro), arq);

    TipoApontador Arvore = NULL;

    for(int i = 0; i < 10000; i++){
        printf("i: %d - Chave: %ld\n", i, registros[i].Chave);
        TipoRegistro reg = registros[i];
        Insere_b_estrela(reg, &Arvore);
    }

    fclose(arq);

    // TipoRegistro x;
    // x.Chave = 14826;

    // if(Pesquisa(&x, &Arvore)) 
    // {
    //     printf("Registro presente na arvore\n");
    //     printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",x.Chave, x.dado1, x.dado2, x.dado3);
    // }
    // else
    // {
    //     printf("Registro não está presente na arvore\n");
    // }

    // TipoRegistro pesquisa;
    // pesquisa.Chave = 1;
    // if(pesquisa_arvore_b(&pesquisa, Arvore))
    //      printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",pesquisa.Chave, pesquisa.dado1, pesquisa.dado2, pesquisa.dado3);

    // else
    //     printf("Não encontrou\n");

    return 0;
}




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
/*
#define END "\x1b[0m"
#define RED_COLOR "\x1b[31m"

void selecionaMetodo(int argc, char * argv[]){

    int metodo = atoi(argv[2]);
    //int quantidade = atoi(argv[3]);
    int situacao = atoi(argv[4]);
    TipoChave chave = atoi(argv[5]);
    //int p = (argc == 7) ? atoi(argv[6]) : 0;

    printf("Metodo: %d, Situacao: %d\n", metodo, situacao);
    
    if(metodo == 1 && situacao == 3){
        printf(RED_COLOR "Nao e possivel utilizar o Acesso Sequencial Indexado com o arquivo desornado aleatoriamente.\n" END);
        return;
    }
    
    char * nomeArquivo = strcat(argv[3], "-arquivo-");

    if(situacao == 1) nomeArquivo = strcat(nomeArquivo, "crescente.bin");
    else if(situacao == 2) nomeArquivo = strcat(nomeArquivo, "decrescente.bin");
    else if(situacao == 3) nomeArquivo = strcat(nomeArquivo, "aleatorio.bin");
    else{
        printf(RED_COLOR "Situacao de arquivo invalida.\n" END);
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
        printf(RED_COLOR "Metodo de pesquisa invalido.\n" END);
        return;
    }
    

}*/