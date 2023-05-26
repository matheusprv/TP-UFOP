#include "acesso_indexado.h"
//#include "arvore_b.h"

int main(int argc, int *argv){
    
    //Teste Acesso Sequencial Indexado
    tipoindice tabela[MAXTABELA];
    FILE *arq; tipoitem x; 
    int pos, cont;
    
    // abre o arquivo de dados
    if((arq = fopen("livros.bin","rb")) == NULL){
        printf("Erro na abertura do arquivo\n");
        return 0;
    }
    //gera a tabela de indice das paginas
    cont = 0; pos = 0;
    while (fread(&x, sizeof(x), 1, arq) == 1)
    {
        cont++;
        if (cont % ITENSPAGINA == 1)
        {
            tabela[pos].chave = x.chave;
            tabela[pos].posicao = pos+1;
            pos++;
        }
    }
    fflush (stdout);
    printf("Codigo do livro desejado: %d", x.chave);

    //ativa a funcao de pesquisa
    if (pesquisa(tabela, pos, &x, arq))
    {
        printf("Livro %s (codigo %d) foi localizado", x.titulo, x.chave);
    }
    else
    {
        printf("Livro de codigo %d nao foi localizado ", x.chave);
    }

    fclose (arq);
    return 0;
}