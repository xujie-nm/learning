#include "SmartPtr.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

class Test
{
    public:
        Test()
        {
            cout << "Test..." << endl;
        }
        ~Test()
        {
            cout << "~Test..." << endl;
        }
};

int main(int argc, const char *argv[])
{
    SmartPtr<Test> ptr(new Test);
    assert(ptr);

    cout << ptr.getPtr() << endl;

    ptr.resetPtr(NULL);

    assert(ptr == false);
    ptr.resetPtr(new Test);

    assert(ptr);
    return 0;
}
