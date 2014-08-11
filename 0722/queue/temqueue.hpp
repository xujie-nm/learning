#ifndef TEMQUEUE_H_
#define TEMQUEUE_H_

#include <stddef.h>

template <typename T>

struct q_node
{
    T data_;
    q_node* next_;
};


template <typename T>

class Queue
{
    public:
        Queue();
        void push(const T& data);
        void pop();
        // T& top();
        const T& top()const;
        void clear();
        bool empty()const;
    private:
        q_node<T>* head_;
        q_node<T>* tail_;
};


template <typename T>
inline Queue<T>::Queue()
            :head_(NULL), tail_(NULL){}

template <typename T>
inline void Queue<T>::push(const T& data)
{
    q_node<T>* pcur = new q_node<T>;
    pcur->data_ = data;
    pcur->next_ = NULL;
    if(head_ == NULL)
    {
        head_ = pcur;
        tail_ = pcur;
    }
    else
    {
        tail_->next_ = pcur;
        tail_ = pcur;
    }
}

template <typename T>
inline void Queue<T>::pop()
{
     if(!empty())
     {
         q_node<T>* pcur = head_;
         head_ = head_->next_;
         delete pcur;
     }
}

template <typename T>
inline const T& Queue<T>::top()const
{
    if(!empty())
    {
        return head_->data_;
    }
}

template <typename T>
inline void Queue<T>::clear()
{
    while(!empty())
    {
        pop();
    }
}

template <typename T>
inline bool Queue<T>::empty()const
{
    return head_ == NULL;
}

#endif  /*TEMQUEUE_H_*/
