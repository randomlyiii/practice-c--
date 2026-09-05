#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    bool flag = true;
    void Solute(TreeNode *left, TreeNode *right)
    {
        if (!flag)
            return;
        if ((left == NULL && right != NULL) || (left != NULL && right == NULL))
        {
            flag = false;
            return;
        }
        if (left == NULL && right == NULL)
            return;
        if (left->val != right->val)
        {
            flag = false;
            return;
        }

        Solute(left->right, right->left);
        Solute(left->left, right->right);
    }
    bool isSymmetric(TreeNode *root)
    {
        flag = true;
        if (root == NULL)
            return true;
        Solute(root->left, root->right);
        return flag;
    }
};

int main()
{
    Solution s;
    // Create a symmetric binary tree for testing
    //       1
    //      / \ 
    //     2   2
    //    / \ / \ 
    //   3  4 4  3
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    cout << (s.isSymmetric(root) ? "true" : "false") << endl;

    return 0;
}