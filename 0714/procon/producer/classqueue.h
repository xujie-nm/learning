#ifndef CLASSQUEUE_H_
#define CLASSQUEUE_H_

#include "Condition.h"
#include "MutexLock.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define SIZE 5

using namespace std;

typedef struct q_node
{
    int data_;
    struct q_node *next_;
}*p_node;

struct List
{
    p_node head_;
    p_node tail_;
    size_t size_;
};

class Queue
{
    private:
        List list;
        MutexLock lock_;
        Condition full_;
        Condition empty_;
        void destory()
        {
            while(is_empty())
            {
                pop();
            }
        }
    public:
        Queue()
        {
            list.head_ = NULL;
            list.tail_ = NULL;
            list.size_ = 0;
        }
        ~Queue()
        {
            destory();
        }
        void push(int data)
        {
            lock_.lock();
            while(list.size_ >= SIZE)
            {
               empty_.wait(lock_.get_lock());
            }
            cout << "producer a data: " << data <<endl;
            //华丽丽的分割线
            p_node cur = (p_node)malloc(sizeof(q_node));
            cur->data_ = data;
            cur->next_ = NULL;
            if(list.head_ == NULL)
            {
                list.head_ = list.tail_ = cur;
            }
            else
            {
                list.tail_->next_ = cur;
                list.tail_ = cur;
            }
            ++list.size_;
            //华丽丽的分割线
            empty_.signal(full_);
            lock_.unlock();
        }
        int top()
        {
            if(is_empty())
            {
                return -1;
            }
            return list.head_->data_;
        }
        void pop()
        {
            lock_.lock();
            while(is_empty())
            {
                cout << "wait producer\n" << endl;
                full_.wait(lock_.get_lock());
            }
            cout << "consume a data" << top() <<endl;
            //华丽丽的分割线
            if(is_empty())
            {
                exit(-1);
            }
            p_node cur = list.head_;
            list.head_ = list.head_->next_;
            free(cur);
            --list.size_;
            //华丽丽的分割线
            full_.signal(empty_);
            lock_.unlock();
        }
        bool is_empty()
        {
            return list.head_ == NULL;
        }
        size_t get_size()
        {
            return list.size_;
        }
};

#endif 
