#include <iostream>
using namespace std;
int main()
{
    int num[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int (*p)[4];
    p = (int (*)[4])num;
    cout << (*(p + 1))[1] << endl; // 6
    printf("%zu\n", sizeof(p));    // 8 因为p是指针，64位系统8个字节
    printf("%p\n", p);
    printf("%p\n", p + 1);
}