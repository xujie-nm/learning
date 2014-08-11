#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>

T abc(T a)
{
    if(a < 0)
        return -a;
    else
        return a;
}

int main(int argc, const char *argv[])
{
    int a = -3;
    int b = 3;
    cout << abc(a) << endl;
    cout << abc(b) << endl;
    return 0;
}
