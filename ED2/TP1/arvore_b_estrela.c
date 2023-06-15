#include "arvore_b_estrela.h"


void Pesquisa(TipoRegistro *x, TipoApontador *Ap){
    int i; 
    TipoApontador Pag;
    Pag = *Ap;
    if((*Ap)->Pt == Interna){
        i = 1;
        while(i < Pag->UU.U0.ni && x->Chave > Pag->UU.U0.ri[i-1]) i++;
        if(x->Chave < Pag->UU.U0.ri[i-1])
            Pesquisa(x, &Pag->UU.U0.pi[i-1]);
        else Pesquisa(x, &Pag->UU.U0.pi[i]);
        return;
    }
    i = 1;
    while(i < Pag->UU.U1.ne && x->Chave > Pag->UU.U1.re[i-1].Chave) 
        i++;
    if(x->Chave == Pag->UU.U1.re[i-1].Chave)
        *x = Pag->UU.U1.re[i-1];
    else 
        print("TipoRegistro nao esta presente na arvore\n");
}

/*
A operacao de insercao de um item em uma arvore B* e essencialmente igual a insercao de um item na arvore B.
Diferenca: Quando uma folha e dividida em duas, o algoritmo promove uma copia da chave que pertence ao item do meio para
a pagina pai no nivel anterior, retendo o proprio item do meio na pagina folha da direita.
*/

/*
void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir) {
    bool NaoAchouPosicao;
    int k;
    k = Ap->n;
    NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao) {
        if (Reg.Chave >= Ap->r[k - 1].Chave) {
            NaoAchouPosicao = false;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1)
            NaoAchouPosicao = false;
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void Ins(TipoRegistro Reg, TipoApontador Ap, short* cresceu, TipoRegistro* RegRetorno, TipoApontador* ApRetorno) {
    long i = 1;
    long j;

    TipoApontador ApTemp;

    if (Ap == NULL) {
        *cresceu = true;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;

        return;
    }

    while (i < Ap->n && Reg.Chave > Ap->r[i - 1].Chave)
        i++;

    if (Reg.Chave == Ap->r[i - 1].Chave) {
        printf("Erro: Registro ja esta presente\n");
        *cresceu = false;

        return;
    }

    if (Reg.Chave < Ap->r[i - 1].Chave)
        i--;

    Ins(Reg, Ap->p[i], cresceu, RegRetorno, ApRetorno);

    if (!*cresceu)
        return;

    if (Ap->n < MM) { // pagina tem espaco
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *cresceu = false;

        return;
    }

    // Overflow: pagina tem que ser dividida
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if (i < M + 1) {
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } else
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);

    for (j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);

    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador* Ap) {
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina* ApRetorno, * ApTemp = (TipoPagina*)malloc(sizeof(TipoPagina));

    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

    if (Cresceu) {
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}
*/


void InsereNaPagina (TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir){
    bool NaoAchouPosicao;
    int k; 
    k = Ap->; 
    NaoAchouPosicao = (k > 0);
    
    while(NaoAchouPosicao){
        if(Reg.Chave >= Ap->r[k-1].Chave){
            NaoAchouPosicao = false;
            break;
        }
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        if(k < 1)
            NaoAchouPosicao = false;
    }
    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}

void Ins(TipoRegistro Reg, TipoApontador Ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno){
    long i = 1;
    long j;
    
    TipoApontador ApTemp;
    
    if(Ap == NULL){
        *cresceu = true;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;

        return;
    }

    while(i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)
        i++;

    if(Reg.Chave == Ap->r[i-1].Chave){
        printf("Erro: Registro ja esta presente\n");
        *cresceu = false;
        
        return;
    }

    if(Reg.Chave < Ap->r[i-1].Chave)
        i--;

    Ins(Reg, Ap->p[i], cresceu, RegRetorno, ApRetorno);

    if(!*cresceu)
        return;
        
    if(Ap->n < MM){ //pagina tem espaco
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *cresceu = false;

        return;
    }

    //Overflow: Pagina tem que ser dividida
    ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if(i < M + 1){
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    }
    
    else
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
        
    for(j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
        
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp = malloc(sizeof(TipoPagina));

    Ins(Reg, *Ap, &Cresceu,&RegRetorno, &ApRetorno);
    
    if(Cresceu){
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap; 
        *Ap = ApTemp;
    }
}