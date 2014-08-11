#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(int* &a, int* &b)
{
    int *temp;
    temp = a;
    a = b;
    b = temp;
}


int main(int argc, const char *argv[])
{
    int *a;
    int *b;

    cout << "the point a: " << a << endl << "the point b: " << b << endl;
    swap(a,b);
    cout << "the point a: " << a << endl << "the point b: " << b << endl;
    return 0;
}
