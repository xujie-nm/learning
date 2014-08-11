#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_

#include <pthread.h>
#include <assert.h>
#include "NonCopyable.h"

class MutexLock : NonCopyable
{
    public:
        MutexLock();
        ~MutexLock();
        void lock();
        void unlock();

        pthread_mutex_t *getMutexPtr()
        {
            return &mutex_;
        }

        bool isLocked()const
        {
            return isLocked_;
        }
    private:
        pthread_mutex_t mutex_;
        bool isLocked_;
};

inline MutexLock::MutexLock()
    :isLocked_(false)
{
    pthread_mutex_init(&mutex_, NULL);
}

inline MutexLock::~MutexLock()
{
    assert(isLocked_ == false);
    pthread_mutex_destroy(&mutex_);
}

inline void MutexLock::lock()
{
    pthread_mutex_lock(&mutex_);
    isLocked_ = true;
}

inline void MutexLock::unlock()
{
    pthread_mutex_unlock(&mutex_);
    isLocked_ = false;
}
#endif  /*MUTEXLOCK_H_*/
