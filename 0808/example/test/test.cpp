#include <cstring>
//#include <string.h>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    
    char buf2[10];
    char buf1[10];
    cout << "please input two string:" << endl;
    cin >> buf1 >> buf2;
    cout << "is equal ?  " << std::strcmp(buf1, buf2) << std::endl;
    return 0;
}
