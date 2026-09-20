// # LeetCode72 编辑距离 动态规划完整思路
// 题目：给定两个单词 word1 和 word2，计算将 word1 转换成 word2 的最少操作次数。
// 允许三种操作：插入一个字符、删除一个字符、替换一个字符。

// ## 操作等价性分析
// 直接看有6种操作（对A增删改、对B增删改），但存在等价关系，本质只有3类：
// 1. 对A删除字符 ⇔ 对B插入字符；
// 2. 对B删除字符 ⇔ 对A插入字符；
// 3. 修改A的一个字符 ⇔ 修改B的一个字符。

// 因此只需要考虑三种核心操作：在A插入字符、在B插入字符、修改A的字符。
// > 操作顺序不影响最终结果，我们只需要考虑在字符串末尾执行操作，简化子问题。

// ## 子问题定义
// 定义 D[i][j]：word1 的前 i 个字符，转化为 word2 的前 j 个字符，所需要的最少编辑距离。

// 举例：A=horse，B=ros
// D[i][j] 代表 horse前i个字符转为 ros前j个字符的最小操作次数。

// ## 子问题推导
// D[i][j] 可以由 D[i][j-1]、D[i-1][j]、D[i-1][j-1] 三个子问题得到：
// 1. D[i][j-1]：A前i字符，B前j-1字符。
//    操作：在A末尾插入B的第j个字符，代价+1。候选值 D[i][j-1] + 1。
// 2. D[i-1][j]：A前i-1字符，B前j字符。
//    操作：删除A的第i个字符，代价+1。候选值 D[i-1][j] + 1。
// 3. D[i-1][j-1]：A前i-1字符，B前j-1字符。
//    - 如果A第i字符 != B第j字符：替换A第i字符，代价+1，候选值 D[i-1][j-1]+1
//    - 如果A第i字符 == B第j字符：无需操作，候选值 D[i-1][j-1]

// ## 状态转移方程
// 情况1：A第i个字符 == B第j个字符
// D[i][j] = min(D[i][j-1]+1, D[i-1][j]+1, D[i-1][j-1])

// 情况2：A第i个字符 != B第j个字符
// D[i][j] = 1 + min(D[i][j-1], D[i-1][j], D[i-1][j-1])

// ## 边界条件
// D[i][0]：word1前i个字符转为空串，只能逐个删除，D[i][0] = i
// D[0][j]：空串转为word2前j个字符，只能逐个插入，D[0][j] = j

// ## 算法流程
// 1. 获取两个字符串长度n、m；若其中一个为空，直接返回n+m。
// 2. 开辟二维DP数组 D[n+1][m+1]，初始化边界。
// 3. 双重循环遍历i从1~n，j从1~m，按转移方程填充DP表。
// 4. D[n][m]即为word1完整字符串转为word2完整字符串的最小编辑距离。

// ## 复杂度
// 时间复杂度：O(n*m)，双重循环填充DP表格
// 空间复杂度：O(n*m)；可优化为一维数组，降低到O(min(n,m))

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size(), n = word2.size();
        int **dp = new int *[m + 1];
        for (int i = 0; i <= m; i++)
        {
            dp[i] = new int[n + 1]();
            dp[i][0] = i;
            if (i > 0)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (word1[i - 1] == word2[j - 1])
                    {
                        dp[i][j] += 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1] - 1));
                    }
                    else
                    {
                        dp[i][j] += 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
                    }
                }
                continue;
            }
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i][j - 1] + 1;
            }
        }
        return dp[m][n];
    }
};

int main()
{
    Solution solution;
    string word1 = "intention";
    string word2 = "execution";
    int result = solution.minDistance(word1, word2);
    cout << "Minimum edit distance: " << result << endl; // Output: Minimum edit distance: 3
    return 0;
}