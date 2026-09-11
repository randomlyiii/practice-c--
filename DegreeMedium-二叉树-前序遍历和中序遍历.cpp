#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 已知前序、中序遍历，还原二叉树：
// 1. 前序遍历规则：根 → 左子树 → 右子树，**前序第一个元素是当前子树的根**。
// 2. 中序遍历规则：左子树 → 根 → 右子树；在中序数组找到根，**根左侧全部是左子树节点，右侧全部是右子树节点**，统计左子树节点数量`leftSize`。
// 3. 分割前序数组：根之后取`leftSize`个元素作为左子树前序，剩余元素为右子树前序。
// 4. 递归构造左子树、右子树；当前区间无节点（`preL>preR`），返回空节点。

// > 核心公式：`leftSize = 根在中序的下标 - 中序区间左边界`

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
    unordered_map<int, int> pos; // value -> index in inorder

    TreeNode *dfs(vector<int> &pre, vector<int> &in,
                  int preL, int preR,
                  int inL, int inR)
    {
        if (preL > preR)
            return nullptr; // 区间空，返回空节点

        int rootVal = pre[preL];
        TreeNode *root = new TreeNode(rootVal);
        int rootIdx = pos[rootVal];

        int leftSize = rootIdx - inL; // 左子树一共有多少个节点

        // 左子树：pre[preL+1 ~ preL+leftSize]
        root->left = dfs(pre, in, preL + 1, preL + leftSize, inL, rootIdx - 1);
        // 右子树：pre[preL+leftSize+1 ~ preR]
        root->right = dfs(pre, in, preL + leftSize + 1, preR, rootIdx + 1, inR);
        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        pos.clear();
        for (int i = 0; i < static_cast<int>(inorder.size()); i++)
        {
            pos[inorder[i]] = i;
        }
        return dfs(preorder, inorder, 0, static_cast<int>(preorder.size()) - 1,
                   0, static_cast<int>(inorder.size()) - 1);
    }

    void printTree(TreeNode *root) // print the binary tree in a structured format
    {
        if (root == nullptr)
        {
            cout << "(empty)" << endl;
            return;
        }

        int height = getHeight(root);
        int width = (1 << height) + 1;
        vector<string> canvas(2 * height - 1, string(width, ' '));
        int offset = height > 1 ? 1 << (height - 2) : 1;
        drawTree(root, 0, width / 2, offset, canvas);

        for (string &line : canvas)
        {
            size_t last = line.find_last_not_of(' ');
            if (last != string::npos)
                cout << line.substr(0, last + 1);
            cout << endl;
        }
    }

private:
    int getHeight(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        return 1 + max(getHeight(root->left), getHeight(root->right));
    }

    void drawTree(TreeNode *root, int row, int column, int offset,
                  vector<string> &canvas)
    {
        if (root == nullptr)
            return;

        string value = to_string(root->val);
        int start = column - static_cast<int>(value.size()) / 2;
        for (int i = 0; i < static_cast<int>(value.size()); i++)
            canvas[row][start + i] = value[i];

        if (root->left != nullptr)
        {
            int branchOffset = max(offset / 2, 1);
            canvas[row + 1][column - branchOffset] = '/';
            drawTree(root->left, row + 2, column - offset, max(offset / 2, 1), canvas);
        }
        if (root->right != nullptr)
        {
            int branchOffset = max(offset / 2, 1);
            canvas[row + 1][column + branchOffset] = '\\';
            drawTree(root->right, row + 2, column + offset, max(offset / 2, 1), canvas);
        }
    }
};

int main()
{
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    Solution solution;
    TreeNode *root = solution.buildTree(preorder, inorder);

    solution.printTree(root);

    return 0;
}
