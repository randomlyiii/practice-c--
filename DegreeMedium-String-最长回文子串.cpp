#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        if (s.size() <= 1)
        {
            return s;
        }
        string res = "", tmp = "";
        res += s[0];
        int num = 1, n = s.size();
        for (int i = 0; i < n - 1; i++)
        {
            int left = i - 1, right = i + 1;
            if (left >= 0 && right < n)
            {
                while (left >= 0 && right < n)
                {
                    if (s[left] != s[right])
                    {
                        left += 1;
                        right -= 1;
                        break;
                    }
                    left -= 1;
                    right += 1;
                }
                if (left < 0 || right >= n)
                {
                    left += 1;
                    right -= 1;
                }
                tmp = s.substr(left, right - left + 1);
                if (tmp.size() > num)
                {
                    num = tmp.size();
                    res = tmp;
                }
            }

            if (s[i + 1] != s[i])
            {
                continue;
            }
            left = i, right = i + 1;
            if (left < 0 || right >= n)
            {
                continue;
            }
            while (left >= 0 && right < n)
            {
                if (s[left] != s[right])
                {
                    left += 1;
                    right -= 1;
                    break;
                }
                left -= 1;
                right += 1;
            }
            if (left < 0 || right >= n)
            {
                left += 1;
                right -= 1;
            }
            tmp = s.substr(left, right - left + 1);
            if (tmp.size() > num)
            {
                num = tmp.size();
                res = tmp;
            }
        }

        return res;
    }
};

int main()
{
    Solution solution;

    string input = "babad";
    cout << "Enter a string: " << input << endl;
    string result = solution.longestPalindrome(input);
    cout << "Longest palindromic substring: " << result << endl;

    input = "cbbd";
    cout << "Enter a string: " << input << endl;
    result = solution.longestPalindrome(input);
    cout << "Longest palindromic substring: " << result << endl;
    return 0;
}