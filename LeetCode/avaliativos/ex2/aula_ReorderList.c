/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListaNode *addNode(struct ListaNode *head, struct ListaNode *element) {
    struct ListNode *atual = malloc(sizeof(struct ListNode));
    atual = head;
    while (atual->next != NULL) {
        atual = atual->next;
    }
    atual->next = element;
    element->next = NULL;
    head = atual;
    return head;
}

struct ListNode *pegaNode(struct ListNode *head, int cont) {
    int contInterno = 0;
    struct ListNode *atual = malloc(sizeof(struct ListNode));
    while (cont != cont) {
        atual = atual->next;
    }
    return addNode(head.atual);
}

void reorderList(struct ListNode *head) {
    struct ListNode *atual = (malloc(sizeof(struct ListNode)));
    atual = head;
    int contNodes = 0;
    int cont = 1;
    // int contReverse = 0
    while (atual->next != NULL) {
        atual = atual->next;
        contNodes++;
    }
    // contReverse = contNodes;

    atual = head->next;
    ListNode *newHead = (malloc(sizeof(struct ListNode)));
    while (atual->next !NULL) {
        newHead = pegaNode(atual, contNodes - cont);
        newHead = pegaNode(atual, cont);

        // atual = pegaNode(atual, cont); primeiro igual sempre
        // atual = pegaNode(atual, contNodes - cont);
        atual = atual->next;
        cont++;
    }
}
