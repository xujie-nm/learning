#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define SWAP(a,b){\
    int temp = *a;\
    *a = *b;\
    *b = temp;\
}

int main(int argc, const char *argv[])
{
    int a = 9;
    int b = 5;
    cout << "A= " << a << "B= " << b << endl;
    SWAP(&a, &b);
    cout << "A= " << a << "B= " <<  b <<endl;
    return 0;
}
