 #include "arvore_b_estrela.h"
 
void inicializa_b_estrela (TipoApontadorEstrela * Arvore) 
{
    *Arvore = NULL;
}

bool Pesquisa(TipoRegistroEstrela *x, TipoApontadorEstrela *Ap)
{
    int i;
    TipoApontadorEstrela Pag = *Ap;

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

void InsereNaPaginaExterna(TipoApontadorEstrela Ap, TipoRegistroEstrela Reg){
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

void InsereNaPaginaInterna(TipoApontadorEstrela Ap, TipoChave Reg, TipoApontadorEstrela ApDir){
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

void Ins_b_estrela(TipoRegistroEstrela Reg, TipoApontadorEstrela Ap, short *cresceu, TipoChave *RegRetorno, TipoApontadorEstrela *ApRetorno){
    long i = 1;
    long j;

    TipoApontadorEstrela ApTemp;

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

        if(Ap->UU.U1.ne < MMB2){ 
            InsereNaPaginaExterna(Ap, Reg);
            *cresceu = false;
            return;
        }

        //Overflow: Pagina tem que ser dividida
        //Criando uma nova pagina
        ApTemp = (TipoApontadorEstrela) malloc(sizeof(TipoPaginaEstrela));
        ApTemp->UU.U1.ne = 0;
        ApTemp->Pt = Externa;

        //Verifica para onde a chave ira
        if(i < MB2 + 1){
            //Insere o item na pagina que ja existe
            //Coloca o ultimo registro na nova pagina
            InsereNaPaginaExterna(ApTemp, Ap->UU.U1.re[MMB2 - 1]);
            Ap->UU.U1.ne--;
            //Insere o novo item na pagina atual
            InsereNaPaginaExterna(Ap, Reg);
        }

        // Inserindo o item que deu o overflow na pagina vizinha
        else InsereNaPaginaExterna(ApTemp, Reg);
            
        //Colocando os valores excedentes e colocando na pagina nova
        for(j = MB2 + 1; j <= MMB2; j++)
            InsereNaPaginaExterna(ApTemp, Ap->UU.U1.re[j-1]);
            
        Ap->UU.U1.ne = MB2;
        *RegRetorno = Ap->UU.U1.re[MB2].Chave;
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
        if(Ap->UU.U0.ni < MMB){ 
            InsereNaPaginaInterna(Ap, *RegRetorno, *ApRetorno);
            *cresceu = false;

            return;
        }

        //Overflow: Pagina tem que ser dividida
        //Criando uma nova pagina
        ApTemp = (TipoApontadorEstrela) malloc(sizeof(TipoPaginaEstrela));
        ApTemp->UU.U0.ni = 0;
        ApTemp->UU.U0.pi[0] = NULL;
        ApTemp->Pt = Interna;

        //Verifica para onde a chave ira
        if(i < MB + 1){
            //Insere o item na pagina que ja existe
            //Coloca o ultimo registro na nova pagina
            InsereNaPaginaInterna(ApTemp, Ap->UU.U0.ri[MMB - 1], Ap->UU.U0.pi[MMB]);
            Ap->UU.U0.ni--;
            //Insere o novo item na pagina atual
            InsereNaPaginaInterna(Ap, *RegRetorno, *ApRetorno);
        }
        
        // Inserindo o item que deu o overflow na pagina vizinha
        else InsereNaPaginaInterna(ApTemp, *RegRetorno, *ApRetorno);
            
        //Colocando os valores excedentes e colocando na pagina nova
        for(j = MB + 2; j <= MMB; j++)
            InsereNaPaginaInterna(ApTemp, Ap->UU.U0.ri[j-1], Ap->UU.U0.pi[j]);
            
        Ap->UU.U0.ni = MB;
        ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MB + 1];
        *RegRetorno = Ap->UU.U0.ri[MB];
        *ApRetorno = ApTemp;
    }
}


void Insere_b_estrela(TipoRegistroEstrela Reg, TipoApontadorEstrela *Ap){
    //caso seja uma nova arvore
    if(*Ap == NULL){
        TipoPaginaEstrela *ApTemp = (TipoPaginaEstrela *)malloc(sizeof(TipoPaginaEstrela));

        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 1;
        ApTemp->UU.U1.re[0] = Reg;
        *Ap = ApTemp;

        return;
    }
    
    short Cresceu;
    TipoChave RegRetorno;
    TipoPaginaEstrela *ApRetorno, *ApTemp;

    Ins_b_estrela(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

    // arvore cresce na altura pela raiz
    // !Verificar para quando a arvore crescer, pois a raiz deixara de ser externa e passara a ser interna
    if (Cresceu){ 
        ApTemp = (TipoPaginaEstrela *)malloc(sizeof(TipoPaginaEstrela));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 1;
        ApTemp->UU.U0.ri[0] = RegRetorno;
        ApTemp->UU.U0.pi[1] = ApRetorno;
        ApTemp->UU.U0.pi[0] = *Ap;
        *Ap = ApTemp;
    }

}

void arvore_b_estrela(long chave, char * nomeArquivo, int quantidade){
    //Criando a árvore
    FILE * arq = fopen(nomeArquivo, "rb");
    if(arq == NULL){
        printErr("Erro na abertura do arquivo\n");
        return;
    }

    TipoRegistroEstrela * registros = (TipoRegistroEstrela *) malloc(quantidade * sizeof(TipoRegistroEstrela));
    fread(registros, quantidade, sizeof(TipoRegistroEstrela), arq);

    TipoApontadorEstrela Arvore;
    inicializa_b_estrela(&Arvore);

    for(int i = 0; i < quantidade; i++)
        Insere_b_estrela(registros[i], &Arvore);
    
    fclose(arq);
    free(registros);

    //Realizando a pesquisa
    TipoRegistroEstrela pesquisa;
    pesquisa.Chave = chave;

    if(Pesquisa(&pesquisa, &Arvore))
         printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",pesquisa.Chave, pesquisa.dado1, pesquisa.dado2, pesquisa.dado3);
    else
        printErr("Registro não encontrado\n");
}