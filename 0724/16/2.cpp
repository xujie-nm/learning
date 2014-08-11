#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>

ostream& put(ostream &os, const T& a)
{
    os << a << endl;
}

int main(int argc, const char *argv[])
{
    put(cout, string("hello")) ;
    put(cout, 501415926);
    put(cout, "hello");
    return 0;
}
