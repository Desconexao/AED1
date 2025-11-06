// https://leetcode.com/problems/two-sum/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if ((nums[i] + nums[j]) == target) {
                int *arrayIndex = (int *)malloc(sizeof(int) * 2);
                arrayIndex[0] = i;
                arrayIndex[1] = j;
                *returnSize = 2;
                return arrayIndex;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}
