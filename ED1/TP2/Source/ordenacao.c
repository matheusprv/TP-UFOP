#include "ordenacao.h"

struct ponto{
    int x;
    int y;
};

struct trajeto{
    Ponto* pontos;
    char nome[25];
    float deslocamentoTotal;
    float distanciaTotal;
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
    float distancia = 0;
    
    for(int i = 0; i < qtdPontos-1; i++){
        distancia += calcularDeslocamentoParcial(trajetos[index].pontos[i], trajetos[index].pontos[i+1]);
    }

    trajetos[index].distanciaTotal = roundf(distancia * 100) / 100; //Arredondando para duas casa decimais
}

float calcularDeslocamentoParcial(Ponto inicio, Ponto fim){
    float deslocamento = sqrt(
        pow(fim.x - inicio.x  ,2) +
        pow(fim.y - inicio.y   ,2)
    );
    return (float) deslocamento; //Arredondando para duas casa decimais roundf(deslocamento * 100) / 100
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
    
    Trajeto aux;

    //Sort array using the Buuble Sort algorithm
    for(int i = inicio; i < fim; i++){
        for(int j = inicio; j <= fim; j++){
            if(strcmp(a[i].nome, a[j].nome) > 0){
                //swap array[j] and array[j+1]
                aux = a[i];
                a[i] = a[j];
                a[j] = aux;

            }
        }
    }

    /*int i, j;
    Trajeto x, y;

    i = inicio;
    j = fim;
    
    //Quando há somente dois itens, o codigo estava comparando o primeiro com ele mesmo
    int index = (fim - inicio) == 1 ? fim : ( (inicio + fim) / 2 );

    printf("\nInicio: %d  --  Fim: %d\n", inicio, fim);
    printf("fim - inicio = %d\n", fim - inicio);
    printf("fim = %d\n", fim);
    printf("(inicio + fim) / 2 = %d\n", (inicio + fim) / 2);
    printf("index: %d\n", index);


    x = a[index];


    printf("%s --  %s  :  %d\n\n", a[i].nome, x.nome, strcmp(a[i].nome, x.nome));

    while (i <= j)
    {
        //Decrescente
        while (strcmp(a[i].nome, x.nome) > 0 && i < fim)
            i++;
        
        while (strcmp(a[i].nome, x.nome) < 0 && j > inicio)
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
        ordenaNome(a, inicio, j);

    if (i < fim)
        ordenaNome(a, i, fim);*/
}

void ordernacao(Trajeto * trajetos, int qtdTrajetos){

   //Ordenando por ordem decrescente da distancia percorrida
    ordenaDistancia(trajetos, 0, qtdTrajetos - 1);

    //Verificando se há distancias iguais e ordenando o deslocamento
    for(int i = 0; i < qtdTrajetos-1; i++){
        
        if(trajetos[i].distanciaTotal == trajetos[i+1].distanciaTotal){
            //Verificando até qual trajeto vai essa igualdade
            int fim = i;
            while(fim < qtdTrajetos && trajetos[i].distanciaTotal == trajetos[fim].distanciaTotal){
                fim++;
            }

            fim--;

            //Ordenando pelo deslocamento
            ordenaDeslocamento(trajetos, i, fim);
            i = fim;
        }

    }

   //Verificando o deslocamento para ordenar pelo nome
    for(int i = 0; i < qtdTrajetos-1; i++){
        
        if(trajetos[i].distanciaTotal == trajetos[i+1].distanciaTotal && trajetos[i].deslocamentoTotal == trajetos[i+1].deslocamentoTotal){
            //Verificando até qual trajeto vai essa igualdade
            int fim = i;
            while(fim < qtdTrajetos && trajetos[i].distanciaTotal == trajetos[fim].distanciaTotal && trajetos[i].deslocamentoTotal == trajetos[fim].deslocamentoTotal){
                fim++;
            } 

            fim--;

            //Ordenando pelo deslocamento
            ordenaNome(trajetos, i, fim);
            i = fim;
        }

    }


}

void imprime(Trajeto * trajetos, int qtdTrajetos){
    for(int i = 0; i < qtdTrajetos; i++){
        printf("%s %.2f %.2f\n", trajetos[i].nome, trajetos[i].distanciaTotal, trajetos[i].deslocamentoTotal);
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
