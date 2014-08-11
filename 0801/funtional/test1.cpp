#include <iostream>
#include <string>
#include <functional>
using namespace std;

void test(int i, double d, const string &s)
{
    cout << "i = " << i << "  d = " << d << "  s = " << s << endl;
}

int main(int argc, const char *argv[])
{
    function<void (int, double)> fp;
    string s = "foobar";
    fp = bind(&test, std::placeholders::_1,
               std::placeholders::_2,
               s);
    cout << "void(*)(int, double)" << endl;
    fp(100, 3.456);
    
    //
    cout << "void (*)(double, int, const string&)" << endl;
    function<void (double, int, const string &)> fp2;
    fp2 = bind(&test,
                std::placeholders::_2,
                std::placeholders::_1,
                std::placeholders::_3);
    fp2(3.1415926, 23456, "foobar");

    
    cout << "void (*)(const string &, int)" << endl;
    function<void (const string &, int)> fp3;
    double a = 3.14;
    fp3 = bind(&test, 
                std::placeholders::_2,
                a,
                std::placeholders::_1);
    fp3("foobar", 3);

    //
    
    cout << "void(*)(const string &, int, double)" << endl;
    function<void (const string &, int, double) > fp4;
    fp4 = bind(&test,
                std::placeholders::_2,
                std::placeholders::_3,
                std::placeholders::_1);
    fp4("foobar", 3, 3.14);

    //
    
    cout << "void(*)(int)" << endl;
    double a5 = 3.14;
    string s5 = "foobar";
    function<void(int)> fp5;
    fp5 = bind(&test, 
                std::placeholders::_1,
                a5, s5);
    fp5(3);

    //
    cout << "void(*)(const string &)" << endl;
    int i5_5 = 3;
    double a5_5 = 3.14;
    function<void(const string &)> fp5_5;
    fp5_5 = bind(&test, i5_5, a5_5, std::placeholders::_1);
    fp5_5("foobar");

    //
    cout << "void(*)()" << endl;
    int i6 = 3;
    double a6 = 3.14;
    string s6 = "foobar";
    function<void() > fp6;
    fp6 = bind(&test, i6, a6, s6);
    fp6();
    
    return 0;
}
