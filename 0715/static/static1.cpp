#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Test
{
    public:
        void setValue(const string &s, int a)
        {
            s_ = s;
            a_ = a;
        }
        void print()const
        {
            cout << s_ << " " << a_ << endl;
        }
    private:
        string s_;
        int a_;
};
int main(int argc, const char *argv[])
{
    void(Test::*func)(const string &, int) = &Test::setValue;
    void(Test::*func2)()const = &Test::print;
    
    Test t;

    (t.*func)("hello", 12);
    (t.*func2)();

    Test *pt = &t;
    (pt->*func)("test", 99);
    (pt->*func2)();
    return 0;
}
