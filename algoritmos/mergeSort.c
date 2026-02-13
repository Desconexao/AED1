#include <stdio.h>
#include <stdlib.h>

void mergeSort(int array[], int size); // return the new array
void merge(int array[], int left[], int leftSize, int right[],
           int righSize); // merge two ordened arrays

int main() {
    int array[] = {5, 2, 9, 1, 3};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < 5; i++)
        printf("%d ", array[i]);

    mergeSort(array, size); // after that the array is ordened
    printf("after merge: \n");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
}

void mergeSort(int array[], int size) {
    if (size <= 1)
        return; // theres nothing to order
    int mid = size / 2;
    int left[mid], right[size - mid];

    printf("Size = %d, Mid = %d\n", size, mid);

    for (int i = 0; i < mid; i++)
        left[i] = array[i];
    for (int i = mid; i < size; i++)
        right[i - mid] = array[i];
    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(array, left, mid, right,
          size - mid); // join the left size with the right size
}

void merge(int array[], int left[], int leftSize, int right[], int rightSize) {
    printf("\n'merge' func called\n");
    int iLeft = 0, iRight = 0, iArray = 0;

    while (iLeft < leftSize && iRight < rightSize) {
        if (left[iLeft] <= right[iRight]) {
            array[iArray] = left[iLeft];
            iLeft++;
        } else {
            array[iArray] = right[iRight];
            iRight++;
        }
        iArray++;
    }

    while (iLeft < leftSize) {
        array[iArray] = left[iLeft];
        iArray++;
        iLeft++;
    }

    while (iRight < rightSize) {
        array[iArray] = right[iRight];
        iArray++;
        iRight++;
    }
}
