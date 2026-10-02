#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        if (k == 0 || n <= 1)
        {
            return 0;
        }
        vector<vector<int>> dp(n, vector<int>(k * 3, 0)); // buy n, sell n, bool n
        dp[0][0] = -prices[0];
        dp[0][2] = 1;
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], -prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
            dp[i][2] = 1;
            for (int boolk = 5; boolk < k * 3; boolk += 3)
            {
                int tmpbuy = boolk - 2, tmpsell = boolk - 1;
                if (dp[i - 1][boolk])
                {
                    dp[i][boolk] = 1;
                    dp[i][tmpbuy] = max(dp[i - 1][tmpbuy], dp[i - 1][tmpbuy - 2] - prices[i]);
                    dp[i][tmpsell] = max(dp[i - 1][tmpsell], dp[i - 1][tmpbuy] + prices[i]);
                }
                else if (dp[i - 1][boolk - 3])
                {
                    dp[i][boolk] = 1;
                    dp[i][tmpbuy] = max(-prices[i], dp[i - 1][tmpbuy - 2] - prices[i]);
                }
            }
        }
        // for(int i = 0; i < n; i ++){
        //     for(int m = 1; m <= k; m ++){
        //         for(int j = m * 3 - 3; j < m * 3; j ++){
        //             cout << dp[i][j] << " ";
        //         }
        //         cout << endl;
        //     }
        //     cout << endl;//
        // }
        int Max = 0;
        for (int i = 2; i < 3 * k; i += 3)
        {
            if (dp[n - 1][i])
            {
                Max = max(Max, dp[n - 1][i - 1]);
            }
        }
        return Max;
    }
};

int main()
{
    Solution solution;
    int k = 2;
    vector<int> prices = {3, 2, 6, 5, 0, 3};
    cout << solution.maxProfit(k, prices) << endl;
    return 0;
}