#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
void swapX(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

int main(int argc, const char *argv[])
{
   cout << "please input two integers" << endl; 
    int a, b;
    cin >>a >>b;
    swapX(a, b);
    cout << a << "  " << b << endl;
    
    cout << "please input two strings" << endl;
    string a1,b1;
    cin >> a1 >> b1;
    swapX(a1, b1);
    cout << a1 << "  " << b1 << endl;
    
    cout << "please input two float" << endl;
    double m,n;
    cin >> m >> n;
    swapX(m, n);
    cout << m << "  " << n << endl;
    
    return 0;
}
