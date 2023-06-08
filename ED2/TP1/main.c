#include "acesso_indexado.h"
#include "estruturas.h"

void nomeArquivo(char *quantReg, char ordemArq, char *nomeArquivo)
{
    //int quantRegInt = atoi(quantReg);
    //int ordemArqInt = atoi(ordemArq);
    
  
}

int main(int argc, char const *argv[]){
    
    TipoChave i = 9;
    char *nome = "Arquivos/100-arquivo-crescente.bin";
    acessoIndexado(i, nome);

    return 0;
}
