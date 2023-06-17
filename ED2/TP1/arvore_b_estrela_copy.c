#include "arvore_b_estrela.h"

#define MM 5  // Número máximo de chaves de uma página interna
#define MM2 4 // Número máximo de registros de uma página externa

typedef int TipoChave;  // Tipo da chave utilizada na árvore

typedef struct TipoRegistro {
    TipoChave Chave;
    long dado1;
    char dado2[1001];
    char dado3[5001];
} TipoRegistro;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPagina {
    TipoIntExt Pt;
    union {
        struct {
            int ni;
            TipoChave ri[MM];
            struct TipoPagina *pi[MM + 1];
        } U0;
        struct {
            int ne;
            TipoRegistro re[MM2];
        } U1;
    } UU;
} TipoPagina;

typedef struct TipoPagina* TipoApontador;

// Função para criar uma nova página
TipoApontador CriaPagina() {
    TipoApontador pagina = (TipoApontador)malloc(sizeof(TipoPagina));
    pagina->Pt = Externa;
    pagina->UU.U1.ne = 0;
    return pagina;
}

// Função para inserir um registro em uma página externa
void InsereRegistro(TipoRegistro reg, TipoApontador pagina) {
    int i, j;

    // Encontra a posição correta para inserir o registro na página
    for (i = 0; i < pagina->UU.U1.ne && reg.Chave > pagina->UU.U1.re[i].Chave; i++)
        ;

    // Move os registros maiores para a direita
    for (j = pagina->UU.U1.ne; j > i; j--) {
        pagina->UU.U1.re[j] = pagina->UU.U1.re[j - 1];
    }

    // Insere o novo registro
    pagina->UU.U1.re[i] = reg;
    pagina->UU.U1.ne++;
}

// Função para inserir uma chave em uma página interna
void InsereChave(TipoChave chave, TipoApontador pagina, TipoApontador apontador) {
    int i, j;

    // Encontra a posição correta para inserir a chave na página
    for (i = 0; i < pagina->UU.U0.ni && chave > pagina->UU.U0.ri[i]; i++)
        ;

    // Move as chaves maiores para a direita
    for (j = pagina->UU.U0.ni; j > i; j--) {
        pagina->UU.U0.ri[j] = pagina->UU.U0.ri[j - 1];
        pagina->UU.U0.pi[j + 1] = pagina->UU.U0.pi[j];
    }

    // Insere a nova chave
    pagina->UU.U0.ri[i] = chave;
    pagina->UU.U0.pi[i + 1] = apontador;
    pagina->UU.U0.ni++;
}

// Função para inserir um registro na árvore B*
void InsereRegistroArvoreB(TipoRegistro reg, TipoApontador pagina, int *cresceu, TipoApontador *filhoDir) {
    int i;
    TipoApontador paginaAux;

    if (pagina == NULL) {
        *cresceu = 1;
        *filhoDir = NULL;
        return;
    }

    if (pagina->Pt == Externa) {
        InsereRegistro(reg, pagina);
        *cresceu = (pagina->UU.U1.ne > MM2);

        if (*cresceu) {
            paginaAux = CriaPagina();
            paginaAux->UU.U1.ne = MM2 / 2;

            for (i = 0; i < MM2 / 2; i++) {
                paginaAux->UU.U1.re[i] = pagina->UU.U1.re[i + MM2 / 2];
            }

            pagina->UU.U1.ne = MM2 / 2;
            *filhoDir = paginaAux;
        } else {
            *filhoDir = NULL;
        }

        return;
    }

    // Busca na página interna a posição onde o registro deve ser inserido
    i = 0;

    while (i < pagina->UU.U0.ni && reg.Chave > pagina->UU.U0.ri[i]) {
        i++;
    }

    // Chama recursivamente a função para inserir o registro na página adequada
    InsereRegistroArvoreB(reg, pagina->UU.U0.pi[i], cresceu, &paginaAux);

    if (!*cresceu) {
        return;
    }

    // A página filho cresceu, então é necessário ajustar a página pai
    if (pagina->UU.U0.ni < MM) {
        InsereChave(paginaAux->UU.U1.re[0].Chave, pagina, paginaAux);
        *cresceu = 0;
        *filhoDir = NULL;
        return;
    }

    // Divisão da página
    paginaAux = CriaPagina();
    paginaAux->Pt = Interna;
    paginaAux->UU.U0.ni = MM / 2;

    for (i = 0; i < MM / 2; i++) {
        paginaAux->UU.U0.ri[i] = pagina->UU.U0.ri[i + MM / 2];
        paginaAux->UU.U0.pi[i + 1] = pagina->UU.U0.pi[i + MM / 2 + 1];
    }

    pagina->UU.U0.ni = MM / 2;
    *filhoDir = paginaAux;
    *cresceu = 1;
}

// Função principal para inserção de um registro na árvore B*
void InsereRegistroArvoreBPrincipal(TipoRegistro reg, TipoApontador *apontador) {
    int cresceu;
    TipoApontador filhoDir, paginaAux;

    InsereRegistroArvoreB(reg, *apontador, &cresceu, &filhoDir);

    if (cresceu) {
        paginaAux = CriaPagina();
        paginaAux->Pt = Interna;
        paginaAux->UU.U0.ni = 1;
        paginaAux->UU.U0.ri[0] = filhoDir->UU.U1.re[0].Chave;
        paginaAux->UU.U0.pi[0] = *apontador;
        paginaAux->UU.U0.pi[1] = filhoDir;
        *apontador = paginaAux;
    }
}
