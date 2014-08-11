#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T1, typename T2>

T2 add(const T1 &a, const T2 &b)
{
    return a + b;
}

int main(int argc, const char *argv[])
{
    cout << add(3, 5.4) << endl;
    cout << add(string("hello"), string("world")) << endl;
    return 0;
}
