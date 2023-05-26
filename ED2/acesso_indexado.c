#include "acesso_indexado.h"

int pesquisa(tipoindice *tab, int tam, tipoitem *item, FILE *arq)
{
    tipoitem pagina[ITENSPAGINA];
    int i, quantitens;
    long desloc;

    i = 0;
    // procura pela pagina onde o item pode se encontrar
    while (i < tam && tab[i].chave <= item->chave)
        i++;

    // caso a chave desejada seja menor que a 1a chave, o item nao existe no arquivo
    if (i == 0)
        return 0;
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
    desloc = (tab[i - 1].posicao - 1) * ITENSPAGINA * sizeof(tipoitem);
    fseek (arq, desloc, SEEK_SET);
    fread (&pagina, sizeof(tipoitem), quantitens, arq);
    
    // pesquisa sequencial na pagina lida
    for (int i = 0; i < quantitens; i++)
    {
        if (pagina[i].chave == item->chave)
        {
            *item = pagina[i];
            return 1;
        }
        return 0;
    }
}
