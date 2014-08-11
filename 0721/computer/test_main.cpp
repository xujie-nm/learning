#include <iostream>
#include <string>
#include <vector>
#include "Computer.h"
using namespace std;

int main(int argc, const char *argv[])
{
    Asus a;
    Mac m;
    Dall d;
    Computer *pt;

    pt = &a;
    cout << "ASUS price" << endl;
    pt->price();

    pt = &m;
    cout << "Mac price" << endl;
    pt->price();

    pt = &d;
    cout << "Dall price" << endl;
    pt->price();
    return 0;
}
