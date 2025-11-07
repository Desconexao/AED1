/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode *root) {
    if (root == NULL)
        return 0; // theres no depth

    int left = maxDepth(root->left);   // go until leaf
    int right = maxDepth(root->right); // go until leaf

    // compare the deeper left leaf with the deeper right leaf
    if (left > right)
        return 1 + left;
    return 1 + right;
}
