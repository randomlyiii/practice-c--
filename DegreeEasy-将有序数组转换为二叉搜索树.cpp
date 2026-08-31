#include <iostream>
#include <queue>
#include <vector>
using namespace std;

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
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return build(nums, 0, nums.size() - 1);
    }

    // [l, r]闭区间构建树
    TreeNode *build(vector<int> &nums, int l, int r)
    {
        if (l > r)
            return nullptr;        // 递归终止，空节点
        int mid = l + (r - l) / 2; // 取中间偏左，防溢出，等价于(l+r)/2
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = build(nums, l, mid - 1);
        root->right = build(nums, mid + 1, r);
        return root;
    }

    void printTreeByLevel(TreeNode *root)
    {
        if (!root)
        {
            cout << "[]" << endl;
            return;
        }

        queue<TreeNode *> q;
        q.push(root);
        vector<string> ans;

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            if (!node)
            {
                ans.push_back("null");
                continue;
            }

            ans.push_back(to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        }

        while (!ans.empty() && ans.back() == "null")
            ans.pop_back();

        cout << "[";
        for (size_t i = 0; i < ans.size(); ++i)
        {
            if (i > 0)
                cout << ",";
            cout << ans[i];
        }
        cout << "]" << endl;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {-10, -3, 0, 5, 9};
    TreeNode *root = solution.sortedArrayToBST(nums);
    solution.printTreeByLevel(root);
    return 0;
}
