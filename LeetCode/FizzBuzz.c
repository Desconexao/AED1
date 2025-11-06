/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **fizzBuzz(int n, int *returnSize) {
    char **answer = (char **)malloc(sizeof(char *) * n);
    *returnSize = 0;

    for (int i = 0; i < n; i++) {
        int num = i + 1;
        if ((num % 3 == 0) && (num % 5 == 0)) {
            answer[i] = (char *)malloc(sizeof(char) * 9);
            strcpy(answer[i], "FizzBuzz");
        } else if (num % 3 == 0) {
            answer[i] = (char *)malloc(sizeof(char) * 5);
            strcpy(answer[i], "Fizz");
        } else if (num % 5 == 0) {
            answer[i] = (char *)malloc(sizeof(char) * 5);
            strcpy(answer[i], "Buzz");
        } else {
            answer[i] = (char *)malloc(
                sizeof(char) *
                (n + 1)); // we've to go through the entire array...
            sprintf(answer[i], "%d", i + 1);
        }
        (*returnSize)++;
    }
    return answer;
}
