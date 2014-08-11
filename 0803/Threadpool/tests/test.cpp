#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    typedef int* pos;
    int a = 5;

    pos p1(&a);
    cout << *p1 << endl;
    return 0;
}
