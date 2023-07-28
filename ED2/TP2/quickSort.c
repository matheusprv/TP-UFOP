#include "quickSort.h"

void quickSort(InfoOrdenacao * infoOrdenacao){

    FILE * ArqLi = fopen(infoOrdenacao->nomeArquivo, "rb+");
    FILE * ArqEi = fopen(infoOrdenacao->nomeArquivo, "rb+");
    FILE * ArqLEs = fopen(infoOrdenacao->nomeArquivo, "rb+");

    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, infoOrdenacao->quantidade);

    fclose(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);

}


void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir){
    int i, j;
    
    if(Dir - Esq < 1) return;
    
    TipoArea Area = inicializaArea();

    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j);
    
    fflush(*ArqLi);
    fflush(*ArqEi);
    fflush(*ArqLEs);

    if(i - Esq < Dir - j){
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
    }else{
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
    }
}

//Le o dado do arquivo superior
void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer){
    fseek(*ArqLEs, (*Ls - 1) * sizeof(TipoRegistro), SEEK_SET);
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = false;
}

//Le o dado do arquivo inferior
void LeInf(FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer){
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLi);
    (*Li)++;
    *OndeLer = true;
}

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea){
    //Insere UltLido de forma ordenada na Area
    InsereItem(*UltLido, Area); 
    *NRArea = ObterNumCelOcupadas(Area);
}

//Escreve o item no arquivo superior
void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es){
    fseek(*ArqLEs, (*Es - 1) * sizeof(TipoRegistro), SEEK_SET);
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs);
    (*Es)--;
}

//Escreve o item no arquivo inferior
void EscreveMin(FILE **ArqEi, TipoRegistro R, int *Ei)
{
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqEi); (*Ei)++;
}

//Remove o maior valor do pivo
void RetiraMax(TipoArea *Area, TipoRegistro *R, int *NRArea){
    RetiraUltimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

//Remove o menor valor do pivo
void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea){
    RetiraPrimeiro(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j){
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
    double Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = true; 
    TipoRegistro UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof(TipoRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TipoRegistro), SEEK_SET);
    
    *i = Esq - 1; 
    *j = Dir + 1;

    //Lendo ate que os ponteiros de leitura se cruzem
    while(Ls >= Li){
        if(NRArea < TAMAREA - 1){
            if(OndeLer) LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            else LeInf(ArqLi, &UltLido, &Li, &OndeLer);

            InserirArea(&Area, &UltLido, &NRArea);
            continue;
        }
        
        //Lendo na alternancia correta
        //Verifica se os ponteiros de leitura e escrita estao juntos para mudar a alternancia da leitura
        if(Ls == Es) LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else if (Li == Ei) LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        else if (OndeLer) LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else LeInf(ArqLi, &UltLido, &Li, &OndeLer);

        //Tratativa do ultimo item lido
        //Caso em que o ultimo elemento vai para o subarquivo A2 (itens superiores ao pivo)
        if(UltLido.nota > Lsup){
            *j = Es; 
            EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }

        //Caso em que o ultimo elemento vai para o subarquivo A1 (itens inferiores ao pivo)
        if(UltLido.nota < Linf){
            *i = Ei; 
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }   
    
        //Caso em que o ultimo elemento vai para o pivo
        InserirArea(&Area, &UltLido, &NRArea);
        
        //Verificando qual o menor sub arquivo e escrevendo nele
        if(Ei - Esq < Dir - Es){ 
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei); 
            Linf = R.nota;
        }
        else{
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
            Lsup = R.nota;
        }   
    }
    
    while(Ei <= Es){
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
    }

}
    