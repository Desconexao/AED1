#include <stdio.h>
#include <stdlib.h>

typedef long KeyType;
typedef struct Register {
    KeyType Key;
} Register;

typedef struct Node {
    Register Reg;
    struct Node *pEsq, *pDir;
} Node;

void init(Node **raiz);
Node *search(KeyType key, Node *node);
void add(Register key, Node *node);
void delete(KeyType key, Node *node);

int main() {
    Node *arvore = NULL;

    Register r1 = {10};
    Register r2 = {5};
    Register r3 = {15};

    add(r1, arvore);
    add(r2, arvore);
    add(r3, arvore);
    Node *search = search(5, arvore);
    printf("Register: %ld", search->Reg.Key);
}

void init(Node **raiz) { *raiz = NULL; }

Node *search(KeyType key, Node *node) {
    if (node == NULL)
        return NULL;

    if (key < node->Reg.Key)
        return search(key, node->pEsq);

    if (key > node->Reg.Key)
        return search(key, node->pDir);

    return node;
}

void add(Register registro, Node *node) {
    if (node == NULL) {
        node = (Node *)malloc(sizeof(Node));
        node->Reg = registro;
        node->pEsq = NULL;
        node->pDir = NULL;
        return;
    }

    if (registro.Key < node->Reg.Key)
        add(registro, node->pEsq);
    else if (registro.Key > node->Reg.Key)
        add(registro, node->pDir);
    else
        printf("Erro: Register já existe\n");
}

void delete(KeyType key, Node *node) {}
