#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define LIMITE 1000000

int main(){
    
    srand(time(NULL));
    
    //for para os diferentes métodos
    for (int i = 1; i <= 4; i++){
    //Execução de diferentes tamanhos de arquivo
        for(int n = 100; n <= LIMITE; n *=10){
        
            for(int j = 1; j <= 3; j++) //for 1 ate 3 para cada organizacao de arquivo (crescente, decrescente e aleatorio)
            {
                for (int k = 0; k < 10; k++) //Geração de chaves aleatorias
                {
                    char command[20];
                    int method = i; int tamFile = n; int ordFile = j; int key;
                    //Chave de pesquisa
                    key = rand() % LIMITE;

                    //Gerando o comando
                    strcpy(command, "./exe ");

                    //Converte int para string
                    char methodString[10]; char tamFileString[10]; char ordFileString[10]; char keyString[10];
                    sprintf(methodString, "%d", method);
                    sprintf(tamFileString, "%d", tamFile);
                    sprintf(ordFileString, "%d", ordFile);
                    sprintf(keyString, "%d", key);

                    //Concatenacao das strings
                    strcat(command, methodString);
                    strcat(command, " ");
                    strcat(command, tamFileString);
                    strcat(command, " ");
                    strcat(command, ordFileString);
                    strcat(command, " ");
                    strcat(command, keyString);

                    //Execucao do comando
                    system(command);
                }
            }  

            printf("\n\n\n\n\n");
        }

    }
    
    return 0;
}