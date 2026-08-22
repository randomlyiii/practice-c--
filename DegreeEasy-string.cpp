// 输入两个字符串，把字符串 1 中删除所有字符串 2 包含的字符。
// 样例：
// 输入：
// They are students.
// aeiou
// 输出：
// Thy r stdnts.

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    string res;
    for (char ch : s1)
    {
        // 如果ch不在s2中，保留
        if (s2.find(ch) == string::npos)
        {
            res += ch;
        }
    }
    cout << res << endl;
    return 0;
}
