#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    // 定义一个大顶堆和一个小顶堆
    priority_queue<int, vector<int>, less<int>> que_TopMax;
    // priority_queue<int, vector<int>, greater<int>> que_TopMin; // 小顶堆

    // 插入一些数据
    que_TopMax.push(10);
    que_TopMax.push(20);
    que_TopMax.push(15);

    // 没有办法遍历 priority_queue 中的元素，只能通过 pop() 访问堆顶元素

    // 输出并删除堆顶元素
    while (!que_TopMax.empty())
    {
        auto top = que_TopMax.top();
        cout << "Value: " << top << endl;
        que_TopMax.pop();
    }

    return 0;
}