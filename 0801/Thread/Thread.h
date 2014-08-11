#ifndef THREAD_H_
#define THREAD_H_ 

#include <pthread.h>
#include <functional>

class Thread
{
    public:
       Thread(std::function< void(void*) > fp);
       void start();
       void join();
    private:
       std::function<void(void *) > fp_;
       pthread_t tid_;
};

#endif  /*THREAD_H_*/
