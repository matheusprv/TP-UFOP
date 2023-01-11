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

void ordena(){

}

void imprime(Trajeto * trajetos, int qtdTrajetos){
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

Trajeto getTrajeto(Trajeto* trajetos, int index){
    return trajetos[index];
}