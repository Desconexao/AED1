// C has an function to transform int to char, idk which its
// maybe compare string ascii numbers, should be easy
// transform array into string?
// search from highest ascii number in nums
// 0-9 char array to return each number to char. char nums['0', '1', '2', ...] ?
// new array to avoid added numbers, increments countArray
char *largestNumber(int *nums, int numsSize) {
    int contArray = 0, contNewNums = 0, flag = 0;
    // char **char = malloc(sizeof(numsize) * sizeof(char))
    // char numsChar = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //
    // how it could work 00-99? char **string = malloc(sizeof(char));
    int newNums[numsSize];
    int highestNumber = 0;
    // until array len is equal to numsSize
    while (1) {
        for (int i = 0; i < numsSize; i++) {
            for (int j = 0; j < (sizeof(newNums) / sizeof(int)); j++) {
                // compare newNums
                if (newNums[j] == nums[i]) // flag to skip number
                    flag = !flag;
            }
            if (nums[i] > highestNumber) {
                highestNumber = nums[i];
                newNums[contNewNums] = highestNumber;
                contNewNums++;
            }
            if (contArray == numsSize)
                break;
            contArray++;
        }
        if (contArray == numsSize)
            break;
    }
    // strcpy(*string, 'a');
    // printf("%s", string);
    return "";
}
