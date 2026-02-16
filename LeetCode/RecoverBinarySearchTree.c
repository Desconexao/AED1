struct TreeNode *first = NULL;
struct TreeNode *second = NULL;
struct TreeNode *prev = NULL;

void inorder(struct TreeNode *root) {
    if (root == NULL)
        return;

    inorder(root->left);

    if (prev != NULL && prev->val > root->val) {
        if (first == NULL) {
            first = prev;
            second = root;
        } else {
            second = root;
        }
    }

    prev = root;

    inorder(root->right);
}

void recoverTree(struct TreeNode *root) {
    first = NULL;
    second = NULL;
    prev = NULL;

    inorder(root);

    int temp = first->val;
    first->val = second->val;
    second->val = temp;
}
