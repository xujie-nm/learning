#include "Thread.h"
#include "Buffer.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void Thread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void *Thread::threadFunc(void *arg)
{
    Thread *pt = static_cast<Thread*>(arg);
    pt->run();
}

void Thread::run()
{}

void Thread::join()
{
    pthread_join(tid_, NULL);
}

void ProduceThread::run()
{
    while(1)
    {
        int data = rand()%1000;
        cout << "produce a data: " << data << endl;
        buffer_.produce(data);
        sleep(5);
    }
}

void ConsumeThread::run()
{
    while(1)
    {
        int data = buffer_.consume();
        cout << "consume a data " << data << endl;
        sleep(1);
    }
}
