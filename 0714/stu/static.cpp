#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Test
{
    public:
        Test()
        {
            ++sum;
        }
        ~Test()
        {
            --sum;
        }
        void print()
        {
            cout << "sum: " << sum << endl;
        }
    private:
        static int sum;
};
 int Test:: sum = 0;

int main(int argc, const char *argv[])
{
    Test t1, t2, t3;
    t3.print();
    Test t4, t5;
    t5.print();
    t4.print();
    t5.~Test();
    t4.print();
    t3.~Test();
    t1.print();
    return 0;
}
