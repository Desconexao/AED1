
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode *insertIntoBST(struct TreeNode *root, int val) {
    if (root == NULL) {
        struct TreeNode *node =
            (struct TreeNode *)malloc(sizeof(struct TreeNode));
        node->val = val;
        node->left = NULL;
        node->right = NULL;
        return node; // return new node
    }
    // we've to storage the left and right nodes, we couldn't lose pointer
    if (root->val > val)
        root->left = insertIntoBST(root->left, val); // new node to the left
    else if (root->val < val)
        root->right = insertIntoBST(root->right, val); // new node to the right

    return root; // we must return the root
}

// i saved this on my IDE and prettier (formatter) change it...
