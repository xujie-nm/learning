#include <iostream>
#include <string>
#include <vector>
#include "Complex.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Complex c1(1,2);
    Complex c2(c1);
    Complex c3;
    c3 = c2;
    Complex c4;
    c4 = 5;
    cout << c1 << endl;
    cout << c2 << endl;
    cout << c3 << endl;
    cout << c4 << endl;

    Complex c5;
    cout << c1 + c2 << endl;
    cout << c1 - c2 << endl;
    cout << c1 + 3 << "  " << 3 + c1 << endl;
    cout << c2 - 3 << "  " << 3 - c2 << endl;
    cout << c1 * c2 << endl;
    cout << c1/c2 << endl;
    cout << c3.abs() << endl;
    return 0;
}
