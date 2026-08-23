// 山峰数组就是任意 i 使 arr [i-1]==arr [i+1] 成立
// 输入1
// 5
// 2 1 2 1 2
// 输出：0

// 输入2
// 6
// 1 1 4 5 1 4
// 输出：11

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);

    ll max_even = 0, max_odd = 0;
    ll sum_even = 0, sum_odd = 0;
    ll cnt_even = 0, cnt_odd = 0;

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        if(i % 2 == 0) //偶数下标
        {
            max_even = max(max_even, (ll)a[i]);
            sum_even += a[i];
            cnt_even ++;
        }
        else //奇数下标
        {
            max_odd = max(max_odd, (ll)a[i]);
            sum_odd += a[i];
            cnt_odd ++;
        }
    }

    ll cost = (cnt_even * max_even - sum_even) + (cnt_odd * max_odd - sum_odd);
    cout << cost << endl;
    return 0;
}
