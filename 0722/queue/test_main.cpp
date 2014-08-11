#include "temqueue.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    Queue<int> qi;
    qi.push(1);
    qi.push(2);
    qi.push(3);
    qi.push(4);

    while(!qi.empty())
    {
        cout << qi.top() << endl;
        qi.pop();
    }
    
    cout << endl;
    Queue<string> qs;
    qs.push("hello");
    qs.push("world");
    qs.push("i am");
    qs.push("xujie");

    while(!qs.empty())
    {
        cout << qs.top() << endl;
        qs.pop();
    }
    return 0;
}
