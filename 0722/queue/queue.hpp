#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>

typedef struct q_node
{
    T data_;
    q_node *next_;
}*p_node;

template<typedef T>

class Queue
{
   public:
       Queue()
       {
           head = NULL;
           tail = NULL;
       }
       void push(T a);
       void pop();
       void clear();
       T top();
       bool empty();
   private:
       p_node<T> head_;
       p_node<T> tail_;

}
