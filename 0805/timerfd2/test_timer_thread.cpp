#include "TimerThread.h"
#include <iostream>
using namespace std;

void foobar()
{
    cout << "hello" << endl;
}

int main(int argc, const char *argv[])
{
    TimerThread foo;
    foo.setTimer(3, 1);
    foo.setTimerCallback(&foobar);

    foo.startTimerThread();

    sleep(10);

    foo.cancelTimerThread();
    return 0;
}
