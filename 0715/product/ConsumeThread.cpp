#include "ConsumeThread.h"
#include "Buffer.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

ConsumeThread::ConsumeThread(Buffer &buffer)
    :tid_(0), buffer_(buffer)
{

}

void ConsumeThread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void *ConsumeThread::threadFunc(void *arg)
{
    ConsumeThread *pt = static_cast<ConsumeThread *>(arg);
    pt->run();
       
    return NULL;
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

void ConsumeThread::join()
{
    pthread_join(tid_, NULL);
}



