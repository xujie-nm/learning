#include "classqueue.h"

using namespace std;

int main(int argc, const char *argv[])
{   
    Queue Q;
    srand(10086);
    int temp;
    cout << "before" << endl;
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    temp = rand()%100;
    cout << temp << endl;
    Q.push(temp);
    cout << "after" << endl;
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    Q.pop();
    cout << Q.top() << endl;
    return 0;
}
