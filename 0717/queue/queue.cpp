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
            while(!is_empty())
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

        Queue(const Queue &Q) 
        {
            p_node cur1 = Q.list.head_; 
            list.head_ = NULL;
            list.tail_ = NULL; 
            list.size_ = 0;  
            while(cur1 != NULL)
            {
                //               cout << cur->data_ << endl;
                push(cur1->data_);
                cur1 = cur1->next_;
            }
        }

        Queue& operator=(const Queue &Q)  
        {
            if(this != &Q)
            {
                destory();
                p_node cur = Q.list.head_;
                while(cur != NULL)
                {
                    push(cur->data_);
                    cur = cur->next_;
                }
            }
            return *this;
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

int main(int argc, const char *argv[])
{
    Queue q;
    q.push(9);
    q.push(8);
    q.push(7);
    q.push(6);

    cout << "q1 start" << endl;
//有问题
    Queue q1(q);
    while(!q1.is_empty())
    {
        cout << q1.top() << endl;
        q1.pop();
    }
/*    
    cout << "q2 start" << endl;
    Queue q2;
    q2 = q;
    while(!q2.is_empty())
    {
        cout << q2.top() << endl;
        q2.pop();
    }
*/
    return 0;
}
