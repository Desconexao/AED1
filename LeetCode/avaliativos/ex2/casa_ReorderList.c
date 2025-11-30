
/**
* Definition for singly-linked list.
* struct ListNode {
    * int val;
    * struct ListNode *next;
}; */
void reorderList(struct ListNode *head) {
    if (!head || !head->next)
        return;

    struct ListNode *atual = head;

    while (atual->next) {
        struct ListNode *penultimo = atual;
        struct ListNode *ultimo = atual;

        while (ultimo->next != NULL) {
            penultimo = ultimo;
            ultimo = ultimo->next;
        }
        if (atual == penultimo)
            break;
        penultimo->next = NULL;
        ultimo->next = atual->next;
        atual->next = ultimo;
        atual = ultimo->next;
    }
}
