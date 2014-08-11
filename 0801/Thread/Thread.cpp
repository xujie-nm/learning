#include "Thread.h"

using namespace std;


Thread::Thread(function<void(void*)> fp):fp_(fp){}

void Thread::start()
{
    void*(callback)(void*) = (void*(void*))(fp_);
    pthread_create(&tid_, NULL, callback, NULL);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
