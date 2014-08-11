#include <iostream>
#include <string>
#include <vector>
#include "Thread.h"

using namespace std;

void test(int a)
{
    while(1)
    {
        cout << a++ << endl;
        sleep(1);
    }
}

int main(int argc, const char *argv[])
{
    Thread t;

    int a;
    cout << "please input a number:" << endl;
    cin >> a;
    
    function<void()> fp;

    fp = bind(&test, a);

    t.run = fp;

    t.start();

    t.join();
    return 0;
}
