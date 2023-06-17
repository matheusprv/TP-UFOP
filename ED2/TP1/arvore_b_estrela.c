 #include "arvore_b_estrela.h"
 
void inicializa_b_estrela (TipoApontador * Arvore) 
{
    *Arvore = NULL;
}

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
            return Pesquisa(x, &Pag->UU.U0.pi[i - 1]);

        else
            return Pesquisa(x, &Pag->UU.U0.pi[i]);

    }

    i = 1;

    while (i < Pag->UU.U1.ne && x->Chave > Pag->UU.U1.re[i - 1].Chave)
        i++;

    if (x->Chave == Pag->UU.U1.re[i - 1].Chave)
    {
        *x = Pag->UU.U1.re[i - 1];
        return true;
    }
    else
        return false;
}

void InsereNaPaginaExterna(TipoApontador Ap, TipoRegistro Reg){
    bool NaoAchouPosicao;
    int k;  

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

void InsereNaPaginaInterna(TipoApontador Ap, TipoChave Reg, TipoApontador ApDir){
    bool NaoAchouPosicao;
    int k;

    k = Ap->UU.U0.ni;
    NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao)
    {
        if (Reg >= Ap->UU.U0.ri[k - 1])
        {
            NaoAchouPosicao = false;
            break;
        }
        Ap->UU.U0.ri[k] = Ap->UU.U0.ri[k - 1];
        k--;
        if (k < 1)
            NaoAchouPosicao = false;
    }
    Ap->UU.U0.ri[k]= Reg;
    Ap->UU.U0.pi[k + 1] = ApDir;
    Ap->UU.U0.ni++;

}

void Ins_b_estrela(TipoRegistro Reg, TipoApontador Ap, short *cresceu, TipoChave *RegRetorno, TipoApontador *ApRetorno){
    long i = 1;
    long j;

    TipoApontador ApTemp;

    if(Ap->Pt == Externa){
        *cresceu = true;
        *RegRetorno = Reg.Chave;
        *ApRetorno = NULL;

        while(i < Ap->UU.U1.ne && Reg.Chave > Ap->UU.U1.re[i-1].Chave)
            i++;

        //caso ja exista o registro na arvore
        if(Reg.Chave == Ap->UU.U1.re[i-1].Chave){
            *cresceu = false;
            return;
        }

        if(Ap->UU.U1.ne < MM2){ 
            InsereNaPaginaExterna(Ap, Reg);
            *cresceu = false;
            return;
        }

        //Overflow: Pagina tem que ser dividida
        //Criando uma nova pagina
        ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
        ApTemp->UU.U1.ne = 0;
        ApTemp->Pt = Externa;

        //Verifica para onde a chave ira
        if(i < M2 + 1){
            //Insere o item na pagina que ja existe
            //Coloca o ultimo registro na nova pagina
            InsereNaPaginaExterna(ApTemp, Ap->UU.U1.re[MM2 - 1]);
            Ap->UU.U1.ne--;
            //Insere o novo item na pagina atual
            InsereNaPaginaExterna(Ap, Reg);
        }

        // Inserindo o item que deu o overflow na pagina vizinha
        else InsereNaPaginaExterna(ApTemp, Reg);
            
        //Colocando os valores excedentes e colocando na pagina nova
        for(j = M2 + 1; j <= MM2; j++)
            InsereNaPaginaExterna(ApTemp, Ap->UU.U1.re[j-1]);
            
        Ap->UU.U1.ne = M2;
        *RegRetorno = Ap->UU.U1.re[M2].Chave;
        *ApRetorno = ApTemp;

        return;
    }

    else{ //Ap->Pt == Interna
        
        while(i < Ap->UU.U0.ni && Reg.Chave > Ap->UU.U0.ri[i-1]) i++;


        //Verifica se iremos para a sub arvore a esquerda (true) ou direita (false)
        if(Reg.Chave < Ap->UU.U0.ri[i-1]) i--;

        Ins_b_estrela(Reg, Ap->UU.U0.pi[i], cresceu, RegRetorno, ApRetorno);

        if(!*cresceu) return;

        //Verifica se a pagina NAO ira crescer, mesmo apos a recursao e adiciona o item no nodo
        if(Ap->UU.U0.ni < MM){ 
            InsereNaPaginaInterna(Ap, *RegRetorno, *ApRetorno);
            *cresceu = false;

            return;
        }

        //Overflow: Pagina tem que ser dividida
        //Criando uma nova pagina
        ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
        ApTemp->UU.U0.ni = 0;
        ApTemp->UU.U0.pi[0] = NULL;
        ApTemp->Pt = Interna;

        //Verifica para onde a chave ira
        if(i < M + 1){
            //Insere o item na pagina que ja existe
            //Coloca o ultimo registro na nova pagina
            InsereNaPaginaInterna(ApTemp, Ap->UU.U0.ri[MM - 1], Ap->UU.U0.pi[MM]);
            Ap->UU.U0.ni--;
            //Insere o novo item na pagina atual
            InsereNaPaginaInterna(Ap, *RegRetorno, *ApRetorno);
        }
        
        // Inserindo o item que deu o overflow na pagina vizinha
        else InsereNaPaginaInterna(ApTemp, *RegRetorno, *ApRetorno);
            
        //Colocando os valores excedentes e colocando na pagina nova
        for(j = M + 2; j <= MM; j++)
            InsereNaPaginaInterna(ApTemp, Ap->UU.U0.ri[j-1], Ap->UU.U0.pi[j]);
            
        Ap->UU.U0.ni = M;
        ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[M + 1];
        *RegRetorno = Ap->UU.U0.ri[M];
        *ApRetorno = ApTemp;
    }
}


void Insere_b_estrela(TipoRegistro Reg, TipoApontador *Ap){
    //caso seja uma nova arvore
    if(*Ap == NULL){
        TipoPagina *ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));

        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 1;
        ApTemp->UU.U1.re[0] = Reg;
        *Ap = ApTemp;

        return;
    }
    
    short Cresceu;
    TipoChave RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins_b_estrela(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

    // arvore cresce na altura pela raiz
    // !Verificar para quando a arvore crescer, pois a raiz deixara de ser externa e passara a ser interna
    if (Cresceu){ 
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 1;
        ApTemp->UU.U0.ri[0] = RegRetorno;
        ApTemp->UU.U0.pi[1] = ApRetorno;
        ApTemp->UU.U0.pi[0] = *Ap;
        *Ap = ApTemp;
    }

}