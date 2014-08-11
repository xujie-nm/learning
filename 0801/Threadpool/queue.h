#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>
typedef int BOOL;
#define TRUE 1
#define FALSE 0

class Task_t
{
    public:
        void (*thread_callback)(void *);
        void *arg;
};

typedef class q_node
{
    public:
        Task_t data_;
        q_node* next_;
} *p_node;

class Queue
{
    public:
        Queue();
        ~Queue();
        void push(Task_t data);
        void pop();
        void clear();
        Task_t top()const;
        BOOL is_empty()const;
        int get_size()const;

    private:
        p_node head_;
        p_node tail_;
        int size_;
};

#endif  /*QUEUE_H_*/
