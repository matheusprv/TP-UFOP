#include "arvore_b.h"


void inicializa (TipoApontador Arvore){
    Arvore = NULL;
}

bool pesquisa_arvore_b (TipoRegistro *x, TipoApontador Ap){
    if(Ap == NULL) return false;

    long i = 1;
    while(i < Ap->n && x->Chave > Ap->r[i-1].Chave)
        i++;

    if(x->Chave == Ap->r[i-1].Chave){
        *x = Ap->r[i-1];
        return true;
    }

    if(x->Chave < Ap->r[i-1].Chave)
        return pesquisa_arvore_b(x, Ap->p[i-1]);

    else
        return pesquisa_arvore_b(x, Ap->p[i]);
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
    bool NaoAchouPosicao;
    int k = Ap->n; 
    NaoAchouPosicao = (k > 0);
    
    //Procura em qual posicao o item devera ser inserido na pagina
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

//Percorre a arvore procurando qual o local que deve inserir o item
void Ins(TipoRegistro Reg, TipoApontador Ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno){
    long i = 1; //Onde o item deve ser inserido
    long j;
    
    TipoApontador ApTemp;
    
    //Verifica se a arvore esta vazia ou se chegou no nodo folha
    if(Ap == NULL){
        *cresceu = true;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;

        return;
    }

    //Realiza uma pesquisa na pagina para saber se ele existe na arvore
    while(i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)
        i++;

    if(Reg.Chave == Ap->r[i-1].Chave){
        //!Erro: Registro ja esta presente
        *cresceu = false;
        
        return;
    }

    //Verifica se iremos para a sub arvore a esquerda (true) ou direita (false)
    if(Reg.Chave < Ap->r[i-1].Chave) i--;

    Ins(Reg, Ap->p[i], cresceu, RegRetorno, ApRetorno);

    //Quando passar por este if, significa que chegou no nodo folha, entao podemos inserir
    //Tambem ira passar quando o no filho deu overflow e a arvore ira crescer, pois um item subiu
    if(!*cresceu) return;
        
    //Verifica se a pagina NAO ira crescer, mesmo apos a recursao e adiciona o item no nodo
    if(Ap->n < MM){ 
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *cresceu = false;

        return;
    }

    //Overflow: Pagina tem que ser dividida
    //Criando uma nova pagina
    ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    //Verifica para onde a chave ira
    if(i < M + 1){
        //Insere o item na pagina que ja existe
        //Coloca o ultimo registro na nova pagina
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM]);
        Ap->n--;
        //Insere o novo item na pagina atual
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    }
    
    // Inserindo o item que deu o overflow na pagina vizinha
    else InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
        
    //Colocando os valores excedentes e colocando na pagina nova
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
    TipoPagina *ApRetorno, *ApTemp;

    Ins(Reg, *Ap, &Cresceu,&RegRetorno, &ApRetorno);
    
    //Verifica se a raiz da arvore vai crescer a raiz
    if(Cresceu){
        ApTemp = (TipoPagina *) malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap; 
        *Ap = ApTemp;
    }
}