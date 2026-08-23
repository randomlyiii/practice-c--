#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    long double pi = 3.1415926;
    std::cout << std::fixed << std::setprecision(2) << "pi = " << pi << std::endl;
}