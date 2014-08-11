#include <iostream>
#include <string>
#include <vector>
#include "Timer.h"
using namespace std;

void func()
{
    printf("foobar...\n");
}

int main(int argc, const char *argv[])
{
    Timer t;
    t.setTimer(3, 1);
    t.setTimerCallback(func);
    t.runTimer();
    return 0;
}
