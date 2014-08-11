#include "Thread.h"
#include <iostream>
using namespace std;

void threadFunc()
{
    cout << "Hello world" << endl;
}

void threadFunc2(int i)
{
    cout << "i = " << i << " foobar" << endl;
}

int main(int argc, const char *argv[])
{
    Thread t(threadFunc);
    t.start();
    t.join();

    Thread t2(bind(&threadFunc2, 12));
    t2.start();
    t2.join();
    return 0;
}
