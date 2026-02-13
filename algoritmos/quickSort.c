#include <stdio.h>
#include <stdlib.h>

void quickSort(int array[], int iLeft, int iRight);

int main() {
    int array[] = {5, 2, 9, 1, 3};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < 5; i++)
        printf("%d ", array[i]);

    quickSort(array, 0, size - 1); // after that the array is ordened
    printf("after: \n");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
}

void quickSort(int array[], int iLeft, int iRight) {
    int pivot, left = iLeft, right = iRight;
    pivot = array[(left + right) / 2];

    while (left <= right) {
        while (array[left] < pivot)
            left++;
        while (array[right] > pivot) {
            right--;
        }
        if (left <= right) {
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            left++;
            right--;
        }
    }

    if (iLeft < right) {
        quickSort(array, iLeft, right);
    }
    if (iRight > left)
        quickSort(array, left, iRight);
}
