#include "Smart.h"
using namespace std;

int main(int argc, const char *argv[])
{
    SmartPtr ptr(new Animal);
    ptr.resetPtr(NULL);
    ptr.resetPtr(new Animal);
    return 0;
}
