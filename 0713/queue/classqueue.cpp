#include "classqueue.h"

void Queue::destory()
{
    while(is_empty())
    {
         pop();
    }
}
