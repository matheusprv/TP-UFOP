#include "acesso_indexado.h"
#include "estruturas.h"



bool pesquisa(tipoindice *tab, int tam, TipoChave Chave, FILE *arq){
    tipoitem pagina[ITENSPAGINA];
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
            quantItens = (ftell(arq) / sizeof(tipoitem)) % ITENSPAGINA;
            
            if(quantItens == 0) quantItens = ITENSPAGINA;
        }
    }

    // le a pagina desejada do arquivo
    desloc = (i - 1) * ITENSPAGINA * sizeof(tipoitem);
    fseek (arq, desloc, SEEK_SET);
    fread (&pagina, sizeof(tipoitem), quantItens, arq);

    // pesquisa binaria na pagina lida
    TipoRegistro item;
    if(pesquisaBinaria(pagina, Chave, &item))
    {
        printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",item.Chave, item.dado1, item.dado2, item.dado3);
        return true;
    }    
   
    return false;
}

void acessoIndexado(TipoChave chave, char *file){
    
    //Teste Acesso Sequencial Indexado
    tipoindice tabela[MAXTABELA];
    FILE *arq; tipoitem pagina[ITENSPAGINA]; 
    int pos;
    
    // abre o arquivo de dados
    arq = fopen(file, "rb");
    if(arq == NULL){
        printf("Erro na abertura do arquivo\n");
        return;
    }

    //Gera a tabela de indice das paginas
    pos = 0;
    while (fread(pagina, sizeof(TipoRegistro), ITENSPAGINA, arq) != 0){
        tabela[pos].chave = pagina[0].Chave;
        pos++;
    }

    //função de pesquisa
    if(pesquisa(tabela, pos, chave, arq)) 
        printf("\x1b[33mRegistro encontrado\n\x1b[0m");
    else 
        printf("\x1b[31mNão encontrado\n\x1b[0m");

    fclose (arq);
}

bool pesquisaBinaria(tipoitem *pagina, TipoChave chave, TipoRegistro *item) {
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

