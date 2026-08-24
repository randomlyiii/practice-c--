// 给出n+1个数字，前n个为密码可能的数字（0~9），第n+1为密码的最短长度，输出可能的密码串（按字典序）；
// 示例：
// 0,2,3
// 1
// 输出：
// 0
// 2
// 3
// 0,2
// 0,3
// 2,3
// 0,2,3

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// dfs回溯求组合
void dfs(const vector<int> &nums, int start, vector<int> &path, int minLen)
{
    // 当前路径长度大于等于最短长度，输出
    if (path.size() >= minLen)
    {
        for (int i = 0; i < path.size(); ++i)
        {
            if (i > 0)
                cout << ",";
            cout << path[i];
        }
        cout << endl;
    }
    for (int i = start; i < nums.size(); ++i)
    {
        path.push_back(nums[i]);
        dfs(nums, i + 1, path, minLen);
        path.pop_back();
    }
}

int main()
{
    string s;
    getline(cin, s);
    vector<int> data;
    stringstream ss(s);
    string token;

    // 按','分割输入
    while (getline(ss, token, ','))
    {
        data.push_back(stoi(token));
    }

    int minLen = data.back();
    data.pop_back();
    vector<int> nums = data;
    sort(nums.begin(), nums.end()); // 排序保证字典序

    vector<int> path;
    dfs(nums, 0, path, minLen);

    return 0;
}
