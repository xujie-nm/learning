#include "Thread.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
using namespace std;

void *test(void*arg)
{
    while(1)
    {
        sleep(1);
        cout << "hello world" << endl;
    }
}

int main(int argc, const char *argv[])
{
//    function<void(void*)> fp;
//    fp = bind(&test, std::placeholders::_1);
    Thread t1(test);
    t1.start();
    t1.join();
    return 0;
}
