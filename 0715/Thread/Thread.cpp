#include "Thread.h"

using namespace std;


Thread::Thread(ThreadCallBack callBack):callBack_(callBack){}

void Thread::start()
{
    pthread_create(&tid_, NULL, callBack_, NULL);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
