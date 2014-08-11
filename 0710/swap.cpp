#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp; 
}

int main(int argc, const char *argv[])
{
    int a, b;
    cin >>a >>b;
    swap(a,b);
    cout << a << "  " << b;
    return 0;
}
