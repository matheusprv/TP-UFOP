#include "acesso_indexado.h"
#include "estruturas.h"
#include "abp.h"


int main(int argc, char const *argv[]){
    /*
    TipoChave i;
    char *nome = "Arquivos/100-arquivo-crescente.bin";
    while(1){
        printf("Digite uma chave de pesquisa: ");
        scanf("%ld", &i);
        acessoIndexado(i, nome);
    }*/

    char *nome = "Arquivos/100-arquivo-crescente.bin";
    constroiArvore(nome);
    FILE *arq = fopen("abp.bin", "rb");
    
    TipoRegistro x;
    x.Chave = 72;

    if(pequisarAbp(arq, &x))
    {
        printf("Registro encontrado\n");
    }

    fclose(arq);


    return 0;
}
