#include "arvore_b.h"


void inicializa (TipoApontador Arvore){
    Arvore = NULL;
}

void pesquisa (TipoRegistro *x, TipoApontador Ap){
    if(Ap == NULL) {
        printf("Registro não está presente na árvore\n");
        return;
    }

    long i = 1;
    while(i < Ap->n && x->Chave > Ap->r[i-1].Chave)
        i++;

    if(x->Chave == Ap->r[i-1].Chave){
        *x = Ap->r[i-1];
        return;
    }

    if(x->Chave < Ap->r[i-1].Chave)
        pesquisa(x, Ap->p[i-1]);

    else
        pesquisa(x, Ap->p[i]);
}

void imprime (TipoApontador arvore){
    if(arvore == NULL)
        return;

    int i = 0;
    while(i <= arvore->n){
        imprime(arvore->p[i]);
        
        if(i != arvore->n)
            printf("%ld ", arvore->r[i].Chave);

        i++;
    }
}

void InsereNaPagina (TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir){
    short NaoAchouPosicao;
    int k; 
    k = Ap->n; 
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
        printf("Erro: Registro já está presente\n");
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
    short Cresceu;--
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins(Reg, *Ap, &Cresceu,&RegRetorno, &ApRetorno);
    
    if(Cresceu){
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap; 
        *Ap = ApTemp;
    }   
}