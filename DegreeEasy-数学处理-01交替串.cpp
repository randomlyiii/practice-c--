#include <iostream>
#include <string>
using namespace std;

// 01010
// 0 | 1 0      切在0后面
// 0 1 | 0      切在1后面
// 1. `0`，cnt0=1：没有间隔，\(2^{0}=1\)，就 1 种（不切）
// 2. `010`，cnt0=2：1 个间隔，\(2^{1}=2\)
// 两种划分：
// `0 | 10`，`01 | 0` ✔
// 3. `0101010`，cnt0=4：3 个间隔，\(2^3=8\) 种方案

long long power(int base, int exp)
{
    long long result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}
int main()
{
    int n = 5;
    string s = "01010";

    int cnt0 = 0;
    for (char c : s)
    {
        if (c == '0')
            cnt0++;
    }

    if (cnt0 == 0)
    {
        cout << 0 << endl;
        return 0;
    }

    long long ans = 1;
    // ans = 2^(cnt0 -1)
    ans = power(2, cnt0 - 1);
    cout << ans << endl;
    return 0;
}
