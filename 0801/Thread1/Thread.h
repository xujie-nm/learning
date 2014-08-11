#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <functional>

class Thread
{
    public:
        Thread();
        ~Thread();

        void start();
        static void *threadFunc(void *arg);
        std::function<void()> run;
        
        void join();
    private:
        pthread_t tid_;
        int a_;
};

#endif  /*THREAD_H_*/
