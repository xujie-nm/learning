#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>

T abs(T a)
{
    if(a < 0)
        return -a;
    return a;
}

int main(int argc, const char *argv[])
{
    cout << abs(-9.15) << endl;
    return 0;
}
