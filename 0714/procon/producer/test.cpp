#include "Thread.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    Queue  Q;
    Thread t1(12,2,&Q);
    Thread t2(14,1,&Q);
    Thread t3(15,2,&Q);
    t1.start();
    t2.start();
    t3.start();
    t3.join();
    t2.join();
    t1.join();
    return 0;
}
