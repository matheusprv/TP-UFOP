#include "stdbool.h"

#define MM 2
#define MM2 2


typedef long TipoChave; 

typedef struct TipoRegistro { 
    TipoChave Chave; /* outros componentes */
} TipoRegistro;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina { 
    TipoIntExt Pt; 
    union {
        struct { 
            int ni; 
            TipoChave ri[MM]; 
            TipoApontador pi[MM + 1];
        } U0; 
        struct { 
            int ne; 
            TipoRegistro re[MM2];
        } U1;
    } UU;
} TipoPagina;


void Pesquisa(TipoRegistro *X, TipoApontador *Ap);