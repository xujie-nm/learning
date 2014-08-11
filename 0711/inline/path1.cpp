#include <iostream>
#include <string>
#include <vector>

using namespace std;

int push()
{
    int num;
    cin >> num;
    if(num == 1)
    {
        return 1;
    }
    else if(num == 2)
    {
        return 2;
    }
}

int main(int argc, const char *argv[])
{
    push();
    return 0;
}
