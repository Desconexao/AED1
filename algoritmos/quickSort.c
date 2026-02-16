#include <stdio.h>
#include <stdlib.h>

void quickSort(int array[], int iLeft, int iRight);

int main() {
    int array[] = {42, 17, 93, 58, 21, 76, 4,  89, 65, 31, 12, 7,  54,
                   98, 23, 81, 36, 9,  70, 44, 60, 2,  91, 28, 14, 85,
                   39, 73, 6,  50, 19, 67, 83, 25, 10, 95, 48, 34, 72,
                   1,  87, 56, 18, 62, 29, 90, 8,  46, 99, 15};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    quickSort(array, 0, size - 1);
    printf("\n");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
}

void quickSort(int array[], int iLeft, int iRight) {
    if (iLeft >= iRight)
        return;
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

    quickSort(array, iLeft, right);
    quickSort(array, left, iRight);
}
