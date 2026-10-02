#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 1.快慢指针
//  为什么这样能找到入口？
//  设：
//  头节点到环入口的距离为 a
//  环入口到快慢指针相遇点的距离为 b
//  环的长度为 L

// 相遇时：
// slow 走了 a + b
// fast 走了 a + b + nL（n 是 fast 在环内多转的圈数）

// 因为 fast 速度是 slow 的两倍：
// 2(a + b) = a + b + nL
// => a + b = nL
// => a = nL - b = (n - 1)L + (L - b)

// 所以：
// 从 head 走 a 步会到达环入口。
// 从相遇点走 a 步：先走 L - b 步到环入口，再绕 (n - 1) 圈，也会到达环入口。
// 因此，让两个指针分别从 head 和相遇点同速前进，它们一定会在环入口相遇。
ListNode *detectCycle_TwoPointer(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return nullptr;
    }

    ListNode *slow = head;
    ListNode *fast = head;

    // 第一步：判断是否有环，并找到相遇点
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            // 有环，开始找环入口
            ListNode *p = head;
            while (p != slow)
            {
                p = p->next;
                slow = slow->next;
            }
            return p; // 环入口
        }
    }

    // 无环
    return nullptr;
}

// 2.哈希表
#include <set>
ListNode *detectCycle_Hash(ListNode *head)
{
    std::set<ListNode *> set;
    while (head != nullptr)
    {
        if (set.find(head) != set.end())
        {
            return head;
        }
        set.insert(head);
        head = head->next;
    }
    return nullptr;
}

int main()
{
    // 创建一个带环的链表：3 -> 2 -> 0 -> -4 -> 2 (环入口为节点值为 2 的节点)
    ListNode *head = new ListNode(3);
    head->next = new ListNode(2);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(-4);
    head->next->next->next->next = head->next; // 创建环

    // ListNode *entry = detectCycle_TwoPointer(head);
    ListNode *entry = detectCycle_Hash(head);
    if (entry)
    {
        cout << "The cycle entry node value is: " << entry->val << endl;
    }
    else
    {
        cout << "NULL" << endl;
    }

    return 0;
}