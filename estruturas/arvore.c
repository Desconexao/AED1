#include <stdio.h>
#include <stdlib.h>

typedef long TipoChave;
typedef struct Regitro {
    TipoChave Chave;
} Registro;

typedef struct No {
    Registro Reg;
    struct No *pEsq, *pDir;
} No;

void inicializa(No **raiz);
No *pesquisa(TipoChave chave, No *no);
void insere(Registro chave, No *no);
void retira(TipoChave chave, No *no);

int main() {}

void inicializa(No **raiz) { *raiz = NULL; }

No *pesquisa(TipoChave chave, No *no) {
    if (no == NULL)
        return NULL;

    if (chave < no->Reg.Chave)
        return pesquisa(chave, no->pEsq);

    if (chave > no->Reg.Chave)
        return pesquisa(chave, no->pDir);

    return no;
}

void insere(Registro registro, No *no) {
    if (no == NULL) {
        no = (No *)malloc(sizeof(No));
        no->Reg = registro;
        no->pEsq = NULL;
        no->pDir = NULL;
        return;
    }

    if (registro.Chave < no->Reg.Chave)
        insere(registro, no->pEsq);
    else if (registro.Chave > no->Reg.Chave)
        insere(registro, no->pDir);
    else
        printf("Erro: Registro já existe\n");
}

void retira(TipoChave chave, No *no) {}
