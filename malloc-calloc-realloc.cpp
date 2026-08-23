// malloc / calloc / realloc 都来自 C 风格堆内存管理，使用后必须 free。
#include <cstdlib>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Windows 控制台使用 UTF-8，避免中文输出乱码
#endif

    // malloc：优点是速度快、只申请一段原始内存；缺点是不初始化，内容是不确定的。
    int *a = static_cast<int *>(malloc(3 * sizeof(int)));
    if (!a)
        return 1;
    for (int i = 0; i < 3; ++i)
        a[i] = i + 1; // malloc 不初始化，必须先赋值
    cout << "malloc: " << a[0] << ' ' << a[1] << ' ' << a[2] << '\n';

    // calloc：优点是申请数组方便且自动清零；缺点是需要额外清零，通常比 malloc 慢。
    int *b = static_cast<int *>(calloc(3, sizeof(int)));
    if (!b)
    {
        free(a);
        return 1;
    }
    cout << "calloc: " << b[0] << ' ' << b[1] << ' ' << b[2] << " (自动清零)\n";

    // realloc：优点是可以调整原内存大小并保留旧数据；缺点是可能搬家，且新增区域不会自动初始化。
    int *bigger = static_cast<int *>(realloc(a, 5 * sizeof(int)));
    if (!bigger)
    {
        free(a);
        free(b);
        return 1;
    } // 用临时指针，失败时 a 仍有效
    // realloc 成功后旧内存已被它接管，不要再 free 原来的 a；最后 free 新的 a 即可。
    a = bigger;
    a[3] = 4;
    a[4] = 5;
    cout << "realloc: " << a[0] << ' ' << a[1] << ' ' << a[2]
         << ' ' << a[3] << ' ' << a[4] << " (扩容)\n";

    free(a);
    free(b);
}
