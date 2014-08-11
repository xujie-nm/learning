#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
            if(is_empty())
            {
                exit(-1);
            }
            p_node cur = list.head_;
            list.head_ = list.head_->next_;
            free(cur);
            --list.size_;
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
