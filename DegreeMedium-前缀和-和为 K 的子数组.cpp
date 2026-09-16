#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> mp;
        mp[0] = 1; // 前缀和0初始出现1次
        int preSum = 0;
        int ans = 0;
        for (int num : nums)
        {
            preSum += num;
            // 查找 preSum - k 是否存在
            if (mp.find(preSum - k) != mp.end())
            {
                ans += mp[preSum - k];
            }
            mp[preSum]++;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {28, 54, 7, -70, 22, 65, -6};
    int k = 3;
    int result = solution.subarraySum(nums, k);
    cout << "Number of subarrays with sum " << k << ": " << result << endl;
    return 0;
}