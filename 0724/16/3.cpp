#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>

int Compare(const T&a, const T&b)
{
    if(a < b)
        return -1;
    else if(a > b)
        return 1;
    else
        return 0;
}

int main(int argc, const char *argv[])
{
    cout << Compare(string("hello"), string("world")) << endl;
    cout << Compare(3, 2) << endl;
    cout << Compare(1, 1) << endl;
//    cout << Compare("hi", "world") << endl;
    return 0;
}
