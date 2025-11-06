/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *runningSum(int *nums, int numsSize, int *returnSize) {
    int *arraySum = (int *)malloc(sizeof(int) * numsSize);
    arraySum[0] = nums[0];
    for (int i = 1; i < numsSize; i++) {
        arraySum[i] = nums[i] + arraySum[i - 1];
    }
    *returnSize = numsSize;
    return arraySum;
}
