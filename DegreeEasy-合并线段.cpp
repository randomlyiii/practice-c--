#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 输入 `n` 个线段 `[L, R]`，**区间合并**（只要新线段起点落在当前合并区间内就合并，也就是标准区间合并：有交集 / 端点接触就合并），输出：

// 1. 合并之后线段个数
// 2. 合并线段总长度
// 3. 合并线段里最长的那条长度
// 输入格式：
// 第一行一个整数 n (1 ≤ n ≤ 10^5)，表示线段
// 接下来 n 行，每行两个整数 L, R (0 ≤ L < R ≤ 10^9)，表示一条线段的左端点和右端点
// 输入样例：
// 5
// 1 3
// 2 4
// 5 7
// 6 8
// 9 10
// 输出样例：
// 3 7 3
int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first >> v[i].second;
    }

    // 按左端点升序；左端点相同按右端点升序
    sort(v.begin(), v.end(), [](const auto &a, const auto &b)
         {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second; });

    int cnt = 0;            // 合并后线段数量
    long long totalLen = 0; // 总长度
    int maxLen = 0;         // 最长线段长度

    int curL = v[0].first;
    int curR = v[0].second;

    for (int i = 1; i < n; i++)
    {
        if (v[i].first > curR)
        {
            // 和当前区间断开，结算上一段
            cnt++;
            int len = curR - curL;
            totalLen += len;
            maxLen = max(maxLen, len);
            // 开启新区间
            curL = v[i].first;
            curR = v[i].second;
        }
        else
        {
            // 有交集，合并，更新右端
            curR = max(curR, v[i].second);
        }
    }
    // 结算最后一组区间！！
    cnt++;
    int len = curR - curL;
    totalLen += len;
    maxLen = max(maxLen, len);

    printf("%d %lld %d", cnt, totalLen, maxLen);
    return 0;
}
