int compare(char *a, char *b) {
    char ab[22], ba[22];
    strcpy(ab, a);
    strcat(ab, b);
    strcpy(ba, b);
    strcat(ba, a);
    return strcmp(ab, ba);
}

void quickSort(char **array, int iLeft, int iRight) {
    int left = iLeft, right = iRight;
    char *pivot = array[(left + right) / 2];

    while (left <= right) {
        while (compare(array[left], pivot) > 0)
            left++;
        while (compare(array[right], pivot) < 0)
            right--;
        if (left <= right) {
            char *temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            left++;
            right--;
        }
    }

    if (iLeft < right)
        quickSort(array, iLeft, right);

    if (left < iRight)
        quickSort(array, left, iRight);
}

char *largestNumber(int *nums, int numsSize) {
    char **array = malloc(numsSize * sizeof(char *));

    for (int i = 0; i < numsSize; i++) {
        array[i] = malloc(11);
        sprintf(array[i], "%d", nums[i]);
    }

    quickSort(array, 0, numsSize - 1);

    if (array[0][0] == '0') {
        char *res = malloc(2);
        strcpy(res, "0");
        return res;
    }

    int totalLen = 1;
    for (int i = 0; i < numsSize; i++)
        totalLen += strlen(array[i]);
    char *result = malloc(totalLen);
    result[0] = '\0';

    for (int i = 0; i < numsSize; i++)
        strcat(result, array[i]);

    return result;
}
