#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addNome(char *lista, char *nome);
char *removerNome(char *lista, char *nome);
void listar(char *lista);

int main() {
    char *lista = NULL;
    char nome[21];
    int opc;

    do {
        printf("1.Adicionar nome\n2.Remover nome\n3.Listar\n4.Sair\n");
        scanf("%d", &opc);

        switch (opc) {
        case 1:
            lista = addNome(lista, nome);
            break;
        case 2:
            lista = removerNome(lista, nome);
            break;
        case 3:
            listar(lista);
            break;
        case 4:
            break;
        }
    } while (opc != 4);
    free(lista);
}

char *addNome(char *lista, char *nome) {
    printf("nome: ");
    scanf(" %[^\n]", nome);
    strcat(nome, " ");
    if (lista == NULL) {
        /* não precisa multiplicar pq o o tamanho do char é 1, caso contrário
        seria strlen(nome) * sizeof(char)*/
        lista = malloc(strlen(nome) + 1);
        strcpy(lista, nome);
    } else {
        // se já tem algo na string, realoca mais memoria
        int novoTamanho = strlen(lista) + strlen(nome) + 1;
        lista = realloc(lista,
                        novoTamanho); // realloc pode falhar caso falte memoria
        strcat(lista, nome);
    }
    return lista;
}

char *removerNome(char *lista, char *nome) {
    int flag;
    printf("nome para ser removido: ");
    scanf(" %[^\n]", nome);
    if (lista == NULL)
        return NULL;
    int lenLista = strlen(lista);
    int lenNome = strlen(nome);
    for (int iLetra = 0; iLetra < strlen(lista); iLetra++) {
        flag = 1;
        for (int jLetra = 0; nome[jLetra] != '\0'; jLetra++) {
            if (lista[iLetra + jLetra] != nome[jLetra]) {
                flag = 0;
                break;
            }
        }
        // se a flag estiver em 1, quer dizer que achou a palavra na string;
        // seria consideravelmente mais facil utilizar a funcao strstr;
        if (flag) {
            // basicamente move a lista para esquerda, até o começo do nome
            for (int carac = iLetra; carac <= lenLista - lenNome; carac++) {
                lista[carac] = lista[carac + lenNome];
            }
            // pra remover os espaços de palavras removidas que ficam
            // no começo da lista
            if (lista[iLetra] == ' ') {
                for (int espaco = iLetra; espaco <= lenLista; espaco++)
                    lista[espaco] = lista[espaco + 1];
            }

            lenLista = strlen(lista);
            // realloc pode falhar caso falte memoria
            lista = realloc(lista, lenLista + 1);
        }
    }
    return lista;
}

void listar(char *lista) {
    if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    printf("%s | Tamanho:%lu\n", lista, strlen(lista));
}
