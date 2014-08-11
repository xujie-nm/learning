#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Test
{
    public:
        static void draw()
        {
            cout << "draw" << endl;
        }
};

int main(int argc, const char *argv[])
{
    void(*func)() = Test::draw;
    func();
    return 0;
}
