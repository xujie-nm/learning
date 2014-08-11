#include "Thread.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
using namespace std;

void* threadfunc(void*arg)
{
    while(1)
    {
        sleep(1);
        cout << "hello world" << endl;
    }
}

int main(int argc, const char *argv[])
{
    Thread t1(threadfunc);
    t1.start();
    t1.join();
    return 0;
}
