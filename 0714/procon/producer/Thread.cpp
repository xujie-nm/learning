#include "Thread.h"
#include <iostream>
#include <time.h>

using namespace std;

Thread::Thread()
    :tid_(-1)
{
}

Thread::~Thread()
{
}

void Thread::start()
{
    if(a_ == 1)
    {
        pthread_create(&tid_, NULL, consumer, this);
    }
    else if(a_ == 2)
    {
        pthread_create(&tid_, NULL, producer, this);
    }
}

void *Thread::producer(void *arg)
{
    Thread *pt = static_cast<Thread *>(arg);
    pt->runpro();
}

void *Thread::consumer(void *arg)
{
    Thread *pt = static_cast<Thread *>(arg);
    pt->runcon();
}

void Thread::runpro()
{
   while(1)
   {
       int data = rand()%100;
       pq_->push(data);
       sleep(2);
   }
}

void Thread::runcon()
{
   while(1)
   {
       pq_->pop();
   }
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
