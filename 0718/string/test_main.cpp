#include "String.h"
using namespace std;
int main(int argc, const char *argv[])
{
    String s("hello");
    String s1(s);
    String s2;
    s2 = s;
    String s3= "xujie" + s ;
    String s4 = s + "world";
    
    cout << s << endl;
    s.debug();
    s1.debug();
    s2.debug();
    s3.debug();
    s4.debug();
    return 0;
}
