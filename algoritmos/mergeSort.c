#include <stdio.h>
#include <stdlib.h>

void mergeSort(int array[], int size);
void merge(int array[], int left[], int leftSize, int right[], int righSize);

int main() {
    int array[] = {42, 17, 93, 58, 21, 76, 4,  89, 65, 31, 12, 7,  54,
                   98, 23, 81, 36, 9,  70, 44, 60, 2,  91, 28, 14, 85,
                   39, 73, 6,  50, 19, 67, 83, 25, 10, 95, 48, 34, 72,
                   1,  87, 56, 18, 62, 29, 90, 8,  46, 99, 15};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    mergeSort(array, size);
    printf("\n");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
}

void mergeSort(int array[], int size) {
    if (size <= 1)
        return;
    int mid = size / 2;
    int left[mid], right[size - mid];

    for (int i = 0; i < mid; i++)
        left[i] = array[i];
    for (int i = mid; i < size; i++)
        right[i - mid] = array[i];
    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(array, left, mid, right, size - mid);
}

void merge(int array[], int left[], int leftSize, int right[], int rightSize) {
    int iLeft = 0, iRight = 0, iArray = 0;

    while (iLeft < leftSize && iRight < rightSize) {
        if (left[iLeft] <= right[iRight])
            array[iArray++] = left[iLeft++];
        else
            array[iArray++] = right[iRight++];
    }

    while (iLeft < leftSize)
        array[iArray++] = left[iLeft++];

    while (iRight < rightSize)
        array[iArray++] = right[iRight++];
}
