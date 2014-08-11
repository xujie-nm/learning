#include "Thread.h"
#include <iostream>
using namespace std;

class Foo
{
    public:
        void bar()
        {
            cout << "bar" << endl;
        }
        void bar2(int i)
        {
            cout << "bar 2" << endl;
        }
};

int main(int argc, const char *argv[])
{
    Foo foo;
    Thread t(bind(&Foo::bar, &foo));
    t.start();
    t.join();

    Thread t2(bind(&Foo::bar2, &foo, 12));
    t2.start();
    t2.join();
    return 0;
}
