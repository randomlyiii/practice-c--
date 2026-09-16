#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    long long mostPoints(vector<vector<int>> &questions)
    {
        int n = questions.size();
        vector<long long> dp(n + 1); // 解决每道题及以后题目的最高分数
        for (int i = n - 1; i >= 0; --i)
        {
            dp[i] = max(dp[i + 1], questions[i][0] + dp[min(n, i + questions[i][1] + 1)]);
        }
        return dp[0];
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> questions = {{3, 2}, {4, 3}, {4, 4}, {2, 5}};
    long long result = solution.mostPoints(questions);
    cout << "Maximum points: " << result << endl; // Output: Maximum points: 10
    return 0;
}