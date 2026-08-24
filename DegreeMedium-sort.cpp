// 【题目】
// 题目名称：多列排序（模拟SQL ORDER BY）
// 时间限制：1s  内存限制：256MB

// 题目描述：
// 输入n,m，表示n行m列的整数，1<=m<=5。
// 接下来输入n行，每行m个整数。
// 最后输入一行排序指令，格式为：ORDER BY 字段1,字段2 DESC,字段3 ASC ...

// 字段名使用a~e：
// a代表第1列，b代表第2列，c代表第3列，d代表第4列，e代表第5列。
// 每个字段后可以跟排序方式：空、ASC、DESC。DESC表示降序，其余全部视为升序。
// 多个排序条件用逗号隔开，优先级从左到右：仅当前面条件对应列的值相等时，才使用后面的条件进行比较。

// 请按照给定规则对所有行排序，输出排序后的全部数据。

// 输入格式：
// 第一行两个整数 n,m。
// 之后n行，每行m个整数。
// 最后一行为ORDER BY排序语句。

// 输出格式：
// 共n行，每行m个整数，数字之间用空格隔开。

// 数据范围：
// 1 ≤ n ≤ 1000，1 ≤ m ≤ 5，每个数字在int范围内。

// 样例输入：
// 3 2
// 1 2
// 3 4
// 1 3
// ORDER BY a ASC, b DESC

// 样例输出：
// 1 3
// 1 2
// 3 4

// ------------------------
// 【测试样例输入数据】
// 3 2
// 1 2
// 3 4
// 1 3
// ORDER BY a ASC, b DESC

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// 一条排序规则：列下标(0开始)，是否降序
struct Rule
{
    int col;
    bool desc;
};

vector<Rule> rules;

// 去掉字符串前后空格
string trim(const string &s)
{
    size_t l = s.find_first_not_of(" \t");
    if (l == string::npos)
        return "";
    size_t r = s.find_last_not_of(" \t");
    return s.substr(l, r - l + 1);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> data(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> data[i][j];
        }
    }

    // 吃掉换行，读取整行 ORDER BY 字符串
    cin.ignore();
    string line;
    getline(cin, line);

    // 去掉 "ORDER BY " 前缀
    const string prefix = "ORDER BY ";
    size_t pos = line.find(prefix);
    string order_part = line.substr(pos + prefix.size());

    // 按逗号分割各个排序项
    vector<string> items;
    stringstream ss(order_part);
    string token;
    while (getline(ss, token, ','))
    {
        string t = trim(token);
        if (!t.empty())
            items.push_back(t);
    }

    // 解析每一项，例如 "a" / "b DESC" / "c ASC"
    for (auto &item : items)
    {
        stringstream iss(item);
        string name, od;
        iss >> name >> od;

        // a->0, b->1 ... e->4
        char ch = tolower(name[0]);
        int colIdx = ch - 'a';

        bool isDesc = false;
        if (!od.empty())
        {
            transform(od.begin(), od.end(), od.begin(), ::toupper);
            if (od == "DESC")
            {
                isDesc = true;
            }
            // ASC或者其他，默认升序
        }
        rules.push_back({colIdx, isDesc});
    }

    // 排序
    sort(data.begin(), data.end(), [](const auto &r1, const auto &r2)
         {
    for (const auto &rt : rules)
    {
        int v1 = r1[rt.col];
        int v2 = r2[rt.col];
        if (v1 != v2)
        {
            if (rt.desc)
            {
                // DESC降序：大的放前面
                return v1 > v2;
            }
            else
            {
                // ASC升序：小的放前面
                return v1 < v2;
            }
        }
        // 当前列相等，继续下一条规则
    }
    // 全部字段相等，顺序无所谓
    return false; });

    // 输出结果
    for (auto &row : data)
    {
        for (int i = 0; i < (int)row.size(); ++i)
        {
            if (i > 0)
                cout << " ";
            cout << row[i];
        }
        cout << endl;
    }

    return 0;
}
