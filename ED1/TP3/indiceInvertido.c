#include "indiceInvertido.h"
/**
 * @brief Inicia o vetor de IndiceInvertido com todas as chaves vazias
 * 
 * @param IndiceIvertido 
 * @return void
*/
void inicia(IndiceInvertido indiceInv){
    int i;

    for (i = 0; i < M ; i ++) {
        memcpy(indiceInv[i].chave, VAZIO, N);
        indiceInv[i].n = 0;
    }
}


/**
 * @brief Insere um documento e as suas palavras chave no vetor de itens
 * 
 * @param indiceInv vetor de itens
 * @param chave chave do documento
 * @param documento nome do documento a ser inserido
 * 
 * @return bool
*/
bool insereDocumento(IndiceInvertido indiceInv, Chave chave, NomeDocumento documento){
    int indexBusca = busca(indiceInv, chave); 
    //caso a palavra (chave) ja exista no indice invertido, sera adicionado o nome do documento naquele item relacionado a essa chave
    if (indexBusca >= 0){
        strcpy(indiceInv[indexBusca].documentos[indiceInv[indexBusca].n], documento);
        indiceInv[indexBusca].n++;
        return true;
    }

    int j = 0;
    int ini = h (chave , M);

    while ( strcmp (indiceInv[( ini + j) % M ].chave , VAZIO) != 0 && j < M ) {
       j ++; 
    }
    if (j < M){
        //como nao existe a palavra no indice invertido, sera adicionado na posicao (ini+j)%M a palavra(chave) e o nome do documento referente
        strcpy(indiceInv[(ini + j) % M].chave, chave);
        strcpy(indiceInv[(ini + j) % M].documentos[indiceInv[(ini + j) % M].n], documento);
        indiceInv[(ini + j) % M].n++;
        return true;
    }
    return false;
}

int busca(IndiceInvertido indiceInv, Chave chave){
    int j = 0;
    int ini = h(chave, M);

    while(strcmp(indiceInv[( ini + j) % M ].chave , VAZIO) != 0 && strcmp (indiceInv[( ini + j ) % M ].chave , chave) != 0 && j < M ){
        j++;
    }

    if(strcmp(indiceInv[(ini + j) % M].chave, chave) == 0){
        return (ini + j) % M;
    }
    return -1;
}

int consulta(IndiceInvertido indiceInv, Chave *chave, int n, NomeDocumento* documento){

}

void imprime(IndiceInvertido indiceInv){
    for(int i=0; i < M; i++){
        if(strcmp(indiceInv[i].chave, VAZIO) != 0){
            printf("%s -", indiceInv[i].chave);

            for (int j = 0; j < indiceInv[i].n; j++)
                printf(" %s", indiceInv[i].documentos[j]);

            printf("\n");
        }
    }
}


void leEntrada(IndiceInvertido indiceInv, int * nDocumentos){
    scanf("%d", nDocumentos);
    getchar();

    int tamMax = (N * NN) + D; //tamanho maximo de caracteres de cada linha da entrada

    char documentoChaves[tamMax]; // armazena a entrada com documento e suas palavras-chaves

    for(int i = 0; i < *nDocumentos; i++){
        fgets(documentoChaves, tamMax, stdin);
    
        documentoChaves[strcspn(documentoChaves, '\n')] = '\0';

        char * token = strtok(documentoChaves, " ");
        char * nomeDocumento;
        strcpy(nomeDocumento, token);

        token = strtok(NULL, " ");
        while(token != NULL){
            insereDocumento(indiceInv, token, nomeDocumento);
            token = strtok(NULL, " ");
        }
    }
}

void leOpcao(IndiceInvertido indiceInv, char * opcao){
    scanf("%c", opcao);
    getchar();

    if(*opcao == 'I')
        imprime(indiceInv);
        
    else{ // opcao == 'B' - busca palavras no indiceInvertido
        char palavrasBuscadas[N*100];
        fgets(palavrasBuscadas, N*100, stdin);

        //fazer strtok para separar as palavras, usar while e usar a funcao consulta e/ou busca
        //ir salvando os nomes dos documentos em um vetor, ordenar esse vetor com a funcao sort, depois imprimir ele
    }
}

void sort(NomeDocumento* documento, int n){
    mergeSort(documento, 0, n-1);
}

void merge(NomeDocumento *documentos, int l, int m, int r){
    int size_l = (m-l+1);
    int size_r = (r-m);

    NomeDocumento *vet_l = malloc(size_l * sizeof(NomeDocumento));
    NomeDocumento *vet_r = malloc(size_r * sizeof(NomeDocumento));
    int i, j;

    for (i = 0; i < size_l; i++)
        strcpy(vet_l[i], documentos[i + l]);

    for(j = 0; j < size_r; j++)
        strcpy(vet_r[j], documentos[m + j + 1]);
    
    i = 0;
    j = 0;

    for (int k = l; k <= r; k++){
        if(i == size_l)
            strcpy(documentos[k], vet_r[j++]);

        else if(j == size_r)
            strcpy(documentos[k], vet_l[i++]);

        else if(strcmp(vet_l[i], vet_r[j]) >= 0)
            strcpy(documentos[k], vet_l[i++]);

        else
            strcpy(documentos[k], vet_r[j++]);
    }
    
    free(vet_l);
    free(vet_r);
}

void mergeSort(NomeDocumento *documentos, int l, int r){
    int m;
    
    if(l<r){
        m = (l+r) / 2;
        mergeSort(documentos, l, m);
        mergeSort(documentos, m+1, r);
        merge(documentos, l, m, r);
    }
}