#include "estruturas.h"

int main(int argc, char const *argv[])
{
    FILE *arq;
    if ((arq = fopen(argv[1], "rb")) == NULL)
    {
        printf("erro\n");
    }
    TipoRegistro *regs = malloc(atoi(argv[2]) * sizeof(TipoRegistro));

    fread(regs, atoi(argv[2]), sizeof(TipoRegistro), arq);
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        printf("%d\n \t%ld\n \t%s\n \t%s\n\n\n\n", regs[i].Chave, regs[i].dado1, regs[i].dado2, regs[i].dado3);
    }
    free(regs);
    fclose(arq);

    return 0;
}
