#include <stdio.h>
#include <time.h>
#include "../estruturas.h"
#define tam 100000
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    
    FILE *arq ;
    arq = fopen("../Arquivos/100000-aleatorio.bin", "rb");
    TipoRegistro *regs = malloc(tam * sizeof(TipoRegistro));
    
    fread(regs, tam, sizeof(TipoRegistro), arq);
    
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % tam;
        printf("%ld\n", regs[pos].Chave);
    }
    fclose(arq);
    free(regs);
    return 0;
}
