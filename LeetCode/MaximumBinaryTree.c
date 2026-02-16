struct TreeNode *build(int *nums, int left, int right) {
    if (left > right)
        return NULL;

    int maxIndex = left;
    for (int i = left + 1; i <= right; i++) {
        if (nums[i] > nums[maxIndex])
            maxIndex = i;
    }

    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = nums[maxIndex];
    root->left = NULL;
    root->right = NULL;

    root->left = build(nums, left, maxIndex - 1);
    root->right = build(nums, maxIndex + 1, right);

    return root;
}

struct TreeNode *constructMaximumBinaryTree(int *nums, int numsSize) {
    return build(nums, 0, numsSize - 1);
}
