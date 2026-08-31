#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> ump;
        for (int i = 0; i < strs.size(); i++)
        {
            string tmps = strs[i];
            sort(tmps.begin(), tmps.end(), [](auto a, auto b)
                 { return a < b; });
            ump[tmps].push_back(strs[i]);
        }

        vector<vector<string>> res;
        for (auto &item : ump)
        {
            res.push_back(item.second);
        }
        return res;
    }
};

int main()
{
    Solution solution;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result = solution.groupAnagrams(strs);

    for (const auto &group : result)
    {
        cout << "[";
        for (const auto &str : group)
        {
            cout << str << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}