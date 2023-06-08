#include "acesso_indexado.h"
#include "estruturas.h"

/*typedef struct TipoRegistro{
    TipoChave Chave;
    long dado1;
    char dado2[1001];
    char dado3[5001];
} TipoRegistro;*/

bool pesquisa(tipoindice *tab, int tam, TipoChave Chave, FILE *arq)
{
    tipoitem pagina[ITENSPAGINA];
    int i, quantitens;
    long desloc;

    /*
    if((arq = fopen("Arquivos/100-arquivo-crescent.bin","rb")) == NULL){
        printf("Erro na abertura do arquivo\n");
        return false;
    }
    */

    i = 0;
    // procura pela pagina onde o item pode se encontrar
    while (i < tam && tab[i].chave <= Chave) i++;

    // caso a chave desejada seja menor que a 1a chave, o item nao existe no arquivo
    if (i == 0)
        return false;
    else
    {
        // a ultima pagina pode nao estar completa 
        if (i < tam)
            quantitens = ITENSPAGINA;
        else
        {
            fseek(arq, 0, SEEK_END);
            quantitens = (ftell(arq) / sizeof(tipoitem)) % ITENSPAGINA;
            if(quantitens == 0)
                quantitens = 4;
        }
    }

    // le a pagina desejada do arquivo
    desloc = (i - 1) * ITENSPAGINA * sizeof(tipoitem);
    fseek (arq, desloc, SEEK_SET);
    fread (&pagina, sizeof(tipoitem), quantitens, arq);

    // pesquisa sequencial na pagina lida
    for (int i = 0; i < quantitens; i++)
    {
        if (pagina[i].Chave == Chave)
        {
            //*item = pagina[i];
            printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",pagina[i].Chave, pagina[i].dado1, pagina[i].dado2, pagina[i].dado3);
            return true;
        }
    
    }
    return false;
}

void acessoIndexado(TipoChave chave, char *file){
    
    //Teste Acesso Sequencial Indexado
    tipoindice tabela[MAXTABELA];
    FILE *arq; tipoitem pagina[ITENSPAGINA]; 
    int pos/*, cont*/;
    
    // abre o arquivo de dados
    arq = fopen(file, "rb");
    if(arq == NULL){
        printf("Erro na abertura do arquivo\n");
        return;
    }
    //gera a tabela de indice das paginas
    pos = 0;
    while (fread(pagina, sizeof(TipoRegistro), ITENSPAGINA, arq) != 0)
    {
        tabela[pos].chave = pagina[0].Chave;
        printf("entrei em pos: %d chave: %ld\n", pos, tabela[pos].chave);
        pos++;
    }

    //função de pesquisa
    if(pesquisa(tabela, pos, chave, arq) == true) 
        printf("Registro encontrado\n");
    else 
        printf("Não encontrado\n");

    fclose (arq);
}

