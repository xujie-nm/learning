#include "Thread.h"

Thread::Thread(ThreadFunc func)
        :callback_(func),
         tid_(0),
         isStarted_(false)
{}

Thread::~Thread()
{
    if(isStarted_)
    {
        pthread_detach(tid_);
    }
}

struct ThreadData
{
    typedef Thread::ThreadFunc ThreadFunc;
    ThreadFunc func_;

    ThreadData(ThreadFunc func)
            :func_(func)
    {}

    void runThread()
    {
        func_();
    }
};

void *threadFunc(void *arg)
{
    ThreadData *pd = static_cast<ThreadData *>(arg);
    pd->runThread();
    delete pd;
}

void Thread::start()
{
    isStarted_ = true;
    ThreadData *data = new ThreadData(callback_);
    if(pthread_create(&tid_, NULL, threadFunc, data))
    {
        delete data;
    }
}

void Thread::join()
{
    pthread_join(tid_, NULL);
    isStarted_ = false;
}

