#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Queue::Queue():head_(NULL),
               tail_(NULL),
               size_(0)
{}

Queue::~Queue()
{
    clear();
}

void Queue::push(Task_t data)
{
    p_node pt = (p_node)malloc(sizeof(q_node));
    pt->data_ = data;
    pt->next_ = NULL;
    if(is_empty())
    {
        head_ = tail_ = pt;
    }else
    {
        tail_->next_ = pt;
        tail_ = pt;
    }
    ++size_;
}

void Queue::pop()
{
    assert(!is_empty());
    p_node pt = head_;
    head_ = head_->next_;
    free(pt);
    --size_;
}

Task_t Queue::top()const
{
    assert(!is_empty());
    return head_->data_;
}

void Queue::clear()
{
    while(!is_empty())
    {
        pop();
    }
}

BOOL Queue::is_empty()const
{
    return head_ == NULL;
}

int Queue::get_size()const
{
    return size_;
}

