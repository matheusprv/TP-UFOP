#include "acesso_indexado.h"
#include "estruturas.h"

void nomeArquivo(char *quantReg, char ordemArq, char *nomeArquivo)
{
    //int quantRegInt = atoi(quantReg);
    //int ordemArqInt = atoi(ordemArq);
    
  
}

int main(int argc, char const *argv[]){
    
    TipoChave i;
    char *nome = "Arquivos/100-arquivo-crescente.bin";
    while(1){
        printf("Digite uma chave de pesquisa: ");
        scanf("%ld", &i);
        acessoIndexado(i, nome);
    }

    return 0;
}
