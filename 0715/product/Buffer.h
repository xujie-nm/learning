#ifndef BUFFER_H_
#define BUFFER_H_ 

#include "Queue.h"
#include "MutexLock.h"
#include "Condition.h"

class Buffer{
    public:
        Buffer(size_t size);
        ~Buffer();

        bool isEmpty() const;
        bool isFull() const;

        void produce(int data);
        int consume();
    private:
        Queue queue_;
        /*
         * mutable代表在const函数中仍可以被修改
         */
        mutable MutexLock mutex_;
        Condition full_;
        Condition empty_;
        size_t size_;
};

#endif  /*BUFFER_H_*/
