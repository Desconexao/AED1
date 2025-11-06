#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int val;
} MinStack;

MinStack *minStackCreate();
void minStackPush(MinStack *obj, int val);
void minStackPop(MinStack *obj);
int minStackTop(MinStack *obj);
int minStackGetMin(MinStack *obj);
void minStackFree(MinStack *obj);

int main() {
    MinStack *stack = minStackCreate();
    minStackPush(stack, 5);
}

MinStack *minStackCreate() {
    MinStack *stack = (MinStack *)malloc(sizeof(MinStack));
    return stack;
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/
