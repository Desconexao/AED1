typedef struct Node {
    int value;
    struct Node *pNext;
} Node;

typedef struct MyQueue {
    Node *pFirst;
    Node *pLast;
} MyQueue;

MyQueue *myQueueCreate() {
    MyQueue *queue = malloc(sizeof(MyQueue));
    queue->pFirst = NULL;
    queue->pLast = NULL;
    return queue;
}

void myQueuePush(MyQueue *obj, int x) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = x;
    newNode->pNext = NULL;

    if (obj->pLast == NULL) {
        obj->pFirst = newNode;
        obj->pLast = newNode;
    } else {
        obj->pLast->pNext = newNode;
        obj->pLast = newNode;
    }
}

int myQueuePop(MyQueue *obj) {
    if (obj->pFirst == NULL)
        return -1;
    Node *temp = obj->pFirst;
    int val = temp->value;
    obj->pFirst = obj->pFirst->pNext;
    if (obj->pFirst == NULL)
        obj->pLast = NULL;
    free(temp);
    return val;
}

int myQueuePeek(MyQueue *obj) {
    if (obj->pFirst == NULL)
        return -1;
    return obj->pFirst->value;
}

bool myQueueEmpty(MyQueue *obj) { return (obj->pFirst == NULL); }

void myQueueFree(MyQueue *obj) {
    while (!myQueueEmpty(obj)) {
        myQueuePop(obj);
    }
    free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/
