// 516. 最长回文子序列
// premium lock icon
// 相关企业
// 给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。

// 子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

// 示例 1：

// 输入：s = "bbbab"
// 输出：4
// 解释：一个可能的最长回文子序列为 "bbbb" 。
// 示例 2：

// 输入：s = "cbbd"
// 输出：2
// 解释：一个可能的最长回文子序列为 "bb" 。
#include <iostream>
#include <vector>
using namespace std;

// 1.dp[i][j]表示s[i..j]的最长回文子序列长度
// 2.状态转移方程：
//  1) s[i] == s[j]，dp[i][j] = dp[i + 1][j - 1] + 2
//  2) s[i] != s[j]，dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])
class Solution_Base
{
public:
    int longestPalindromeSubseq(string s)
    {
        int n = s.length();
        vector f(n, vector<int>(n));
        for (int i = n - 1; i >= 0; i--)
        {
            f[i][i] = 1;
            for (int j = i + 1; j < n; j++)
            {
                f[i][j] = s[i] == s[j] ? f[i + 1][j - 1] + 2 : max(f[i + 1][j], f[i][j - 1]);
            }
        }
        return f[0][n - 1];
    }
};

// 空间优化版
// dp[j] 表示s[i..j]的最长回文子序列长度
// 用额外空间pre保存f[i+1][j-1]的值
class Solution_SpaceOptimized
{
public:
    int longestPalindromeSubseq(string s)
    {
        int n = s.length();
        vector<int> f(n);
        for (int i = n - 1; i >= 0; i--)
        {
            f[i] = 1;
            int pre = 0; // 初始值为 f[i+1][i]
            for (int j = i + 1; j < n; j++)
            {
                int tmp = f[j];
                f[j] = s[i] == s[j] ? pre + 2 : max(f[j], f[j - 1]);
                pre = tmp;
            }
        }
        return f[n - 1];
    }
};

int main()
{
    Solution_Base solution;
    string s = "bbbab";
    int result = solution.longestPalindromeSubseq(s);
    cout << "The length of the longest palindromic subsequence is: " << result << endl;

    s = "cbbd";
    result = solution.longestPalindromeSubseq(s);
    cout << "The length of the longest palindromic subsequence is: " << result << endl;

    return 0;
}