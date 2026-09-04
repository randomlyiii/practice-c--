#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// 判断字符是否为字母或者数字
bool isAlnum(char c)
{
    return std::isalnum(static_cast<unsigned char>(c)) != 0;
}

/**
 * @param pattern 规则串：字母、数字、?、*
 * @param s 待判断字符串：仅字母数字
 * @return true 匹配成功
 */
bool isMatch(const std::string &pattern, const std::string &s)
{
    int n = pattern.size();
    int m = s.size();

    // dp[i][j]: pattern前i个字符，匹配s前j个字符
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
    dp[0][0] = true;

    // 处理pattern开头连续*，*可以匹配空串
    for (int i = 1; i <= n; ++i)
    {
        if (pattern[i - 1] == '*')
            dp[i][0] = dp[i - 1][0];
        else
            break;
    }

    for (int i = 1; i <= n; ++i)
    {
        char p = pattern[i - 1];
        for (int j = 1; j <= m; ++j)
        {
            char ch = s[j - 1];
            if (p == '?')
            {
                // ? 匹配恰好1个字母数字
                if (isAlnum(ch))
                    dp[i][j] = dp[i - 1][j - 1];
            }
            else if (p == '*')
            {
                // *两种情况：*匹配空(dp[i‑1][j])；*吃掉当前s字符(dp[i][j‑1])
                // 隐含约束：*吃掉的字符一定是字母数字，s本身输入保证
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
            else
            {
                // 普通字母数字，必须严格相等
                if (p == ch)
                    dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    return dp[n][m];
}

int main()
{
    std::string pat = "MP?329*00*e", str = "MPA3290000e328e";
    // std::cin >> pat >> str;
    if (isMatch(pat, str))
        std::cout << "true\n";
    else
        std::cout << "false\n";
    return 0;
}
