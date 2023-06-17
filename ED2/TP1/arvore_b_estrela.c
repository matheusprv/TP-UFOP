#include "arvore_b_estrela.h"

bool Pesquisa(TipoRegistro *x, TipoApontador *Ap)
{
    int i;
    TipoApontador Pag = *Ap;

    if (Pag->Pt == Interna)
    {
        i = 1;

        while (i < Pag->UU.U0.ni && x->Chave > Pag->UU.U0.ri[i - 1])
            i++;

        if (x->Chave < Pag->UU.U0.ri[i - 1])
            Pesquisa(x, &Pag->UU.U0.pi[i - 1]);

        else
            Pesquisa(x, &Pag->UU.U0.pi[i]);

        return;
    }

    i = 1;

    while (i < Pag->UU.U1.ne && x->Chave > Pag->UU.U1.re[i - 1].Chave)
        i++;

    if (x->Chave == Pag->UU.U1.re[i - 1].Chave)
        *x = Pag->UU.U1.re[i - 1];

    else
        print("TipoRegistro nao esta presente na arvore\n");
}

void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir)
{
    bool NaoAchouPosicao;
    int k;
    if (Ap->Pt = Interna)
    {
        k = Ap->UU.U0.ni;
        NaoAchouPosicao = (k > 0);

        while (NaoAchouPosicao)
        {
            if (Reg.Chave >= Ap->UU.U0.ri[k - 1])
            {
                NaoAchouPosicao = false;
                break;
            }
            Ap->UU.U0.ri[k] = Ap->UU.U0.ri[k - 1];
            k--;
            if (k < 1)
                NaoAchouPosicao = false;
        }
        Ap->UU.U0.ri[k]= Reg.Chave;
        Ap->UU.U0.pi[k + 1] = ApDir;
        Ap->UU.U0.ni++;
    }
    else
    {
        k = Ap->UU.U1.ne; 
        NaoAchouPosicao = (k > 0);
    
        while(NaoAchouPosicao){
            if(Reg.Chave >= Ap->UU.U1.re[k-1].Chave){
                NaoAchouPosicao = false;
                break;
            }
            Ap->UU.U1.re[k] = Ap->UU.U1.re[k-1];
            k--;
            if(k < 1)
                NaoAchouPosicao = false;
    }

        Ap->UU.U1.re[k] = Reg;
        Ap->UU.U1.ne++;
    }
    return;
}

bool Ins(TipoRegistro Reg, TipoApontador Ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno){
    long i = 1;
    long j;

    TipoApontador ApTemp;

    if (Ap == NULL){
        *cresceu = true;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;

        return;
    }

    if (Ap->Pt == Interna){

        while (i < Ap->UU.U0.ni && Reg.Chave > Ap->UU.U0.ri[i - 1])
            i++;

        if (Reg.Chave == Ap->UU.U0.ri[i - 1]){
            printf("Erro: Registro ja esta presente\n");
            *cresceu = false;

            return false;
        }

        if (Reg.Chave < Ap->UU.U0.ri[i - 1])
            i--;

        Ins(Reg, Ap->UU.U0.pi[i], cresceu, RegRetorno, ApRetorno);
    }
    
    if (!*cresceu)
        return false;

    if (Ap->Pt < MM){ // pagina tem espaco
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *cresceu = false;

        return false;
    }

    // Overflow: Pagina tem que ser dividida
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if (i < M + 1){
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    }

    else
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);

    for (j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);

    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

    if (Cresceu){ // arvore cresce na altura pela raiz
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->UU.U0.ni = 1;
        ApTemp->UU.U0.ri[0] = RegRetorno.Chave;
        ApTemp->UU.U0.pi[1] = ApRetorno;
        ApTemp->UU.U0.pi[0] = *Ap;
        *Ap = ApTemp;
    }
}

/*
Procurar o local onde o dado deve ser inserido
Adicionar
Verificar se vai estourar a pagina
    Criar uma nova pagina
*/