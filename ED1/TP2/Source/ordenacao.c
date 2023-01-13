#include "ordenacao.h"

struct ponto{
    int x;
    int y;
};

struct trajeto{
    Ponto* pontos;
    char nome[25];
    double deslocamentoTotal;
    double distanciaTotal;
};

Ponto* alocaPontos(int n){
    Ponto * pontos = (Ponto*) malloc(n * sizeof(Ponto));
    return pontos;
}

void desalocaPontos(Ponto* ponto){
    free(ponto);
}

void desalocaTrajeto(Trajeto** trajetos, int qtdTrajetos, int qtdPontos){
    for(int i = 0; i<qtdTrajetos; i++){
        desalocaPontos( (*trajetos)[i].pontos);
    }
    free(*trajetos);
}

void calcularDistancia(Trajeto* trajetos, int index, int qtdPontos){
    double distancia = 0;
    
    for(int i = 0; i < qtdPontos-1; i++){
        distancia += calcularDeslocamentoParcial(trajetos[index].pontos[i], trajetos[index].pontos[i+1]);
    }

    trajetos[index].distanciaTotal = distancia;
}

double calcularDeslocamentoParcial(Ponto inicio, Ponto fim){
    double deslocamento = sqrt(
        pow(fim.x - inicio.x  ,2) +
        pow(fim.y - inicio.y   ,2)
    );
    return deslocamento;
}

void calcularDeslocamento(Trajeto* trajetos, int index, int qtdPontos){
    trajetos[index].deslocamentoTotal = calcularDeslocamentoParcial( trajetos[index].pontos[0], trajetos[index].pontos[qtdPontos - 1]);
}


void ordenaDistancia(Trajeto * a, int inicio, int fim){
    int i, j;
    Trajeto x, y;

    i = inicio;
    j = fim;
    x = a[(inicio + fim) / 2];

    while (i <= j)
    {
        //Decrescente
        while (a[i].distanciaTotal > x.distanciaTotal && i < fim)
            i++;
        
        while (a[j].distanciaTotal < x.distanciaTotal && j > inicio)
            j--;

        if (i <= j)
        {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if (j > inicio)
        ordenaDistancia(a, inicio, j);

    if (i < fim)
        ordenaDistancia(a, i, fim);
}

void ordenaDeslocamento(Trajeto * a, int inicio, int fim){
    int i, j;
    Trajeto x, y;

    i = inicio;
    j = fim;
    x = a[(inicio + fim) / 2];

    while (i <= j)
    {
        //Decrescente
        while (a[i].deslocamentoTotal < x.deslocamentoTotal && i < fim)
            i++;
        
        while (a[j].deslocamentoTotal > x.deslocamentoTotal && j > inicio)
            j--;

        if (i <= j)
        {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if (j > inicio)
        ordenaDeslocamento(a, inicio, j);

    if (i < fim)
        ordenaDeslocamento(a, i, fim);
}

void ordenaNome(Trajeto * a, int inicio, int fim){

}

void ordernacao(Trajeto * trajetos, int qtdTrajetos){
    
    /*
        Ordem decrescente da distancia percorrida
        Ordem crescente do deslocamento
        Ordem crescente do nome
    */

   //Ordenando por ordem decrescente da distancia percorrida
    ordenaDistancia(trajetos, 0, qtdTrajetos - 1);

    imprime(trajetos, qtdTrajetos);

    //Verificando se há distancias iguais e ordenando o deslocamento
    for(int i = 0; i < qtdTrajetos-1; i++){
        
        if(trajetos[i].distanciaTotal == trajetos[i+1].distanciaTotal){
            //Verificando até qual trajeto vai essa igualdade
            int fim = i;
            while(fim < qtdTrajetos && trajetos[i].distanciaTotal == trajetos[fim].distanciaTotal){
                fim++;
            }

            fim--;

            printf("\nQTD Trajetos: %d\nInicio: %d\nFim: %d\n", qtdTrajetos, i, fim);
            //Ordenando pelo deslocamento
            ordenaDeslocamento(trajetos, i, fim);
            i = fim;
        }

    }


}

void imprime(Trajeto * trajetos, int qtdTrajetos){
    printf("NOME Dist Desl\n");
    for(int i = 0; i < qtdTrajetos; i++){
        printf("%s %.2lf %.2lf\n", trajetos[i].nome, trajetos[i].distanciaTotal, trajetos[i].deslocamentoTotal);
    }
}

Trajeto* alocaTrajetos(int n){
    Trajeto* trajetos = (Trajeto*) malloc(n * sizeof(Trajeto));

    if(trajetos == NULL){
        exit(1);
    }
    return trajetos;
}

void lerTrajetos(int qtdTrajetos, int qtdPontos, Trajeto* trajetos){
    
    for(int i = 0; i < qtdTrajetos; i++){
        scanf("%s", trajetos[i].nome);
        getchar();

        trajetos[i].pontos = alocaPontos(qtdPontos);
        
        for(int j = 0; j < qtdPontos; j++){
            scanf("%d", &trajetos[i].pontos[j].x);
            scanf("%d", &trajetos[i].pontos[j].y);
        }
    }


}
