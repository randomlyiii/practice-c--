#include <iostream>
using namespace std;
class A
{
public:
    virtual void draw() { cout << "A" << endl; }
    virtual void info()
    {
        cout << "Info Start" << endl;
        draw(); // ❗重点：这里调用draw()，是虚调用！
        cout << "Info End" << endl;
    }
};

class B : public A
{ // public继承！B是A的公有子类
public:
    void draw() override { cout << "B" << endl; }
    void info() override { cout << "B Info" << endl; }
};

class C : public A
{ // public继承
public:
    void draw() override { cout << "C" << endl; }
};

int main()
{
    A *ptr;
    B b;
    C c;
    ptr = &b;
    ptr->draw();
    ptr->info();
    ptr = &c;
    ptr->draw();
    ptr->info();
}

// C++多态实现原理及意义

// 一、多态分类

// C++ 多态分为两类：

// 1. 静态多态（编译期多态）
//    包括函数重载、运算符重载、模板、CRTP 等。
//    特点：编译期确定调用哪个函数，通常没有运行时额外开销。

// 2. 动态多态（运行期多态）
//    通过继承 + 虚函数 + 基类指针/引用实现。
//    特点：运行时根据对象真实类型决定调用哪个函数。

// 下面重点讲动态多态。

// 二、动态多态的实现原理

// 主流编译器通常用“虚函数表 vtable + 虚表指针 vptr”实现。

// 1. 虚函数表 vtable

// 如果一个类含有虚函数，编译器会为这个类生成一张虚函数表。
// vtable 本质上是一个函数指针数组，里面存放该类虚函数的地址。

// 例如：

// class Base {
// public:
//     virtual void f() { cout << "Base::f\n"; }
//     virtual void g() { cout << "Base::g\n"; }
//     virtual ~Base() {}
// };

// class Derived : public Base {
// public:
//     void f() override { cout << "Derived::f\n"; }
//     void g() override { cout << "Derived::g\n"; }
// };

// 可以粗略理解为：

// Base 的 vtable:
// [0] -> Base::f
// [1] -> Base::g
// [2] -> Base::~Base

// Derived 的 vtable:
// [0] -> Derived::f
// [1] -> Derived::g
// [2] -> Derived::~Derived

// 如果派生类没有重写某个虚函数，则 vtable 对应位置仍然指向基类版本。

// 2. 虚表指针 vptr

// 每个含有虚函数的对象内部，通常会有一个隐藏指针，叫 vptr，指向所属类的 vtable。

// 对象布局可以粗略理解为：

// Derived 对象：
// +--------+
// | vptr   | ---> Derived 的 vtable
// +--------+
// | 成员变量 |
// +--------+

// vtable 属于类，所有对象共享；vptr 属于对象，每个对象都有一份。

// 3. 虚函数调用过程

// 当通过基类指针或引用调用虚函数时：

// Base* p = new Derived;
// p->f();

// 编译器不会直接写死调用 Base::f，而是生成类似这样的间接调用：

// (*(p->vptr[0]))(p);

// 过程是：

// 1. 通过对象指针 p 找到 vptr；
// 2. 通过 vptr 找到 vtable；
// 3. 按编译期确定的槽位索引取出函数地址；
// 4. 调用该地址对应的函数。

// 因此，p 实际指向 Derived 对象，就调用 Derived::f；
// 指向 Base 对象，就调用 Base::f。这就是动态绑定。

// 4. 构造和析构期间的虚函数

// 在构造函数和析构函数中调用虚函数，不会发生派生类重写后的动态绑定。

// 原因：
// 构造基类部分时，vptr 先指向基类 vtable；
// 构造派生类部分时，才指向派生类 vtable。
// 析构则相反。

// 所以：

// class Base {
// public:
//     Base() { f(); }  // 调用的是 Base::f，不是 Derived::f
//     virtual void f() { cout << "Base::f\n"; }
// };

// 不要在构造/析构中依赖虚函数的多态行为。

// 5. 虚析构函数

// 如果打算通过基类指针删除派生类对象，基类析构函数必须是虚函数：

// class Base {
// public:
//     virtual ~Base() = default;
// };

// class Derived : public Base {
// public:
//     ~Derived() { /* 释放资源 */ }
// };

// Base* p = new Derived;
// delete p;  // 若析构非虚，只调用 Base::~Base，Derived 资源泄漏

// 虚析构保证先调用派生类析构，再调用基类析构。

// 6. 纯虚函数和抽象类

// 纯虚函数：

// virtual void draw() = 0;

// 含有纯虚函数的类是抽象类，不能实例化。
// 派生类必须实现所有纯虚函数才能实例化。
// 这常用于定义接口。

// 三、动态多态的意义

// 1. 统一接口，屏蔽差异
//    基类定义接口，派生类提供不同实现。
//    调用者只依赖基类接口，不关心具体类型。

// 2. 解耦调用方和实现方
//    调用代码不需要知道对象到底是 Circle 还是 Square，
//    只需知道它是 Shape。

// 3. 可扩展性强，符合开闭原则
//    新增类型时，通常只需新增派生类，不必修改已有调用代码。

// 4. 支持框架和插件式设计
//    框架定义基类/接口，用户派生实现。
//    例如图形系统、GUI 事件、网络协议处理、游戏对象系统。

// 5. 支持运行时决策
//    程序可以根据实际对象类型，在运行时选择正确行为。

// 四、动态多态的代价

// 1. 每个多态对象多一个 vptr，增加内存开销；
// 2. 虚函数调用需要间接寻址，通常不能内联，性能略低；
// 3. 对象布局和调试更复杂；
// 4. 多重继承、虚继承下 vtable 更复杂，可能有多个 vptr。

// 静态多态，如模板和 CRTP，则没有这些运行时开销，
// 但灵活性和适用场景不同。

// 五、总结

// C++ 动态多态的核心是：

// 基类指针/引用 + 虚函数 + vtable/vptr => 运行时动态绑定

// 它让程序面向接口编程，提高扩展性和解耦性；
// 代价是对象变大、调用变慢、实现复杂。

// 实际设计中：
// 需要运行时替换实现时，常用动态多态；
// 追求性能和泛型编程时，常用静态多态。