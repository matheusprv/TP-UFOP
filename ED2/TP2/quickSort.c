#include "quickSort.h"

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir){
    int i, j;
    
    TipoArea Area;

    if(Dir - Esq < 1) return;
    FAVazia(&Area);

    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j);
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

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea)
{
    //Insere UltLido de forma ordenada na Area
    InsereItem(*UltLido, Area); *NRArea = ObterNumCelOcupadas(Area);
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
void RetiraMin(Tipo *Area, TipoRegistro *R, int *NRArea){
    RetiraUltimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j){
    int Ls = Dir, Es = Dir, Li = Esq, NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = true; TipoRegistro UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof(TipoRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TipoRegistro), SEEK_SET);
    
    *i = Esq - 1; *j = Dir + 1;

    //Lendo até que os ponteiros de leitura se cruzem
    while(Ls >= Li){
        if(NRArea < TAMAREA - 1){
            if(OndeLer) LeSup(ArqEi, &UltLido, &Ls, &OndeLer);
            else LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserirArea(&Area, &UltLido, &NRArea);
            continue;
        }
        
        //Verifica se os ponteiros de leitura e escrita estao juntos para mudar a alternancia da leitura
        if(Ls == Es) LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else if (Li == Ei) LeInf(ArqLi, &UltLido, &Li, &OndeLer);

        //Lendo na alternancia correta
        else if (OndeLer) LeSup(ArqLEs, &UltLido, &Ls. &OndeLer):
        else Lelnf(ArqLi, &UltLido, &Li, &OndeLer);


        //Tratativa do ultimo item lido
        
        //Caso em que o ultimo elemento vai para o subarquivo A2 (itens superiores ao pivo)
        if(UltLido.Chave > Lsup){
            *j = Es; EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }

        //Caso em que o ultimo elemento vai para o subarquivo A1 (itens inferiores ao pivo)
        if(UltLido.Chave < Linf){
            *i = Ei; EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }   
    
        //Caso em que o ultimo elemento vai para o pivo
        InserirArea(&Area, &UltLido, &NRArea);
        
        //Verificando qual o menor sub arquivo e escrevendo nele
        if(Ei - Esq < Dir - Es){ 
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei); Lsup = R.Chave;
        }
        else{
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
            Lsup = R.Chave;
        }   
    }
    
    while(Ei <= Es){
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
    }

}
    