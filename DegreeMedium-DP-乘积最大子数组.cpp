#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int n = nums.size();
        long long max_dp = nums[0];
        long long min_dp = nums[0];
        long long ans = nums[0];
        for (int i = 1; i < n; i++)
        {
            long long cur = nums[i];
            // 保存旧max，不然更新max_dp后min_dp计算会用新值
            long long pre_max = max_dp;
            max_dp = max(cur, max(pre_max * cur, min_dp * cur));
            // 负数，更新min_dp，可能会负负得正
            min_dp = min(cur, min(pre_max * cur, min_dp * cur));
            ans = max(ans, max_dp);
        }
        return (int)ans;
    }
};

int main()
{
    int nums[] = {2, 3, -2, 4};
    vector<int> vec(nums, nums + sizeof(nums) / sizeof(int));
    Solution s;
    cout << s.maxProduct(vec) << endl;
    return 0;
}