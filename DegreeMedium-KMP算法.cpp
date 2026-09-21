#include <iostream>
#include <vector>
#include <string>
using namespace std;
// KMP算法的核心是next数组（前缀函数）的构建
// 只适合连续子串匹配问题（找主串T中连续等于模式串S的片段）
// next[k]=L 的含义：S[0..L-1] == S[k-L+1..k]
// 含义：S[0~k]这个子串，最长的相等真前缀、真后缀长度为L
// KMP匹配失败时：
//  利用上面这个相等关系，不用从S[0]从头比对，直接跳到S[L]继续比对，省去0~L-1的重复检查
//  如果L=0（没有相等前后缀），则模式串指针回到S[0]重新开始匹配
// 如果完整匹配整个模式串（全部字符对上）：
//  不是直接回到0！而是 j = next[ns-1]，继续查找【重叠】的匹配

class Solution
{
public:
    int Count(const string &S, const string &T)
    {
        int ns = S.size(), nt = T.size();
        if (ns == 0 || nt == 0 || ns > nt)
            return 0;
        // KMP-构建next数组
        vector<int> next(ns, 0);
        for (int i = 1; i < ns; ++i)
        {
            int k = next[i - 1];
            while (k > 0 && S[i] != S[k])
                k = next[k - 1];
            if (S[i] == S[k])
                k++;
            next[i] = k;
        }
        // KMP匹配
        int cnt = 0;
        int j = 0; // S指针
        for (int i = 0; i < nt; ++i)
        {
            while (j > 0 && T[i] != S[j])
                j = next[j - 1];
            if (T[i] == S[j])
                j++;
            if (j == ns)
            {
                cnt++;
                j = next[j - 1]; // 继续找下一个重叠匹配
            }
        }
        return cnt;
    }
};
int main()
{
    string S = "ababab", T = "abababab";
    Solution sol;
    cout << sol.Count(S, T) << endl; // 输出2
}
