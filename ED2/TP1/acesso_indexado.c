#include "acesso_indexado.h"
#include "cores.h"

bool pesquisa(Indice *tab, int tam, TipoChave Chave, FILE *arq){
    TipoRegistro pagina[ITENSPAGINA];
    int i, quantItens;
    long desloc;

    i = 0;
    // procura pela pagina onde o item pode ser encontrado
    while (i < tam && tab[i].chave <= Chave) i++;

    // caso a chave desejada seja menor que a primeira chave, o item nao existe no arquivo
    if (i == 0) return false;
    
    else{
        // a ultima pagina pode nao estar completa 
           if (i < tam) quantItens = ITENSPAGINA;
        
        else {
            fseek(arq, 0, SEEK_END);
            quantItens = (ftell(arq) / sizeof(TipoRegistro)) % ITENSPAGINA;
            
            if(quantItens == 0) quantItens = ITENSPAGINA;
        }
    }

    // le a pagina desejada do arquivo
    desloc = (i - 1) * ITENSPAGINA * sizeof(TipoRegistro);
    fseek (arq, desloc, SEEK_SET);
    fread (&pagina, sizeof(TipoRegistro), quantItens, arq);

    // pesquisa binaria na pagina lida
    TipoRegistro item;
    if(pesquisaBinaria(pagina, Chave, &item))
    {
        printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",item.Chave, item.dado1, item.dado2, item.dado3);
        return true;
    }    
   
    return false;
}

bool pesquisaBinaria(TipoRegistro *pagina, TipoChave chave, TipoRegistro *item) {
    int inicio = 0;
    int fim = ITENSPAGINA - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (pagina[meio].Chave == chave){
            *item = pagina[meio];
            return true;
        }
        
        if (pagina[meio].Chave < chave)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return false; // Retorna falso se o valor não for encontrado
}

//Gera a tabela de indices e retorna o seu tamanho
int geraTabela(Indice * tabela, FILE ** arq, char *nomeArquivo){

    // abre o arquivo de dados
    *arq = fopen(nomeArquivo, "rb");
    if(*arq == NULL){
        printErr("Erro na abertura do arquivo\n");
        return -1;
    }

    TipoRegistro pagina[ITENSPAGINA]; 
    int pos;

    //Gera a tabela de indice das paginas
    pos = 0;
    while (fread(pagina, sizeof(TipoRegistro), ITENSPAGINA, *arq) != 0){
        tabela[pos].chave = pagina[0].Chave;
        pos++;
    }

    return pos;
}

void acessoIndexado(TipoChave chave, char *nomeArquivo){

    //Gera a tabela de indices a partir do arquivo de dados
    FILE * arq = NULL; 
    Indice tabela[MAXTABELA];
    int tam = geraTabela(tabela, &arq, nomeArquivo);

    if(tam == -1) return;

    //função de pesquisa
    if(pesquisa(tabela, tam, chave, arq))   printf("\x1b[33mRegistro encontrado\n\x1b[0m");
    else printErr("Registro não encontrado\n");

    fclose (arq);
}