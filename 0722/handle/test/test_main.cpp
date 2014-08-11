#include "Animal.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    Animal *pt;
    pt = new Cat;
    pt->display();
    pt = new Dog;
    pt->display();
    pt = new Bear;
    pt->display();
    return 0;
}
