#ifndef _CONDITION_H_
#define _CONDITION_H_ 

#include <pthread.h>

//condition中仅包含Mutex的引用，所以不需要头文件
class MutexLock;

class Condition
{
    public:
        Condition(MutexLock &lock);
        ~Condition();
        void wait();
        void notify();
        void notifyAll();

    private:
        pthread_cond_t cond_;
        MutexLock &lock_;
};

#endif  /*_CONDITION_H_*/
