
int height(struct TreeNode *root) {
    if (root == NULL)
        return 0;

    int left = height(root->left);
    int right = height(root->right);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

bool isBalanced(struct TreeNode *root) {
    if (root == NULL)
        return true;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight - rightHeight > 1)
        return false;
    if (rightHeight - leftHeight > 1)
        return false;

    return isBalanced(root->left) && isBalanced(root->right);
}
