#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T, size_t N>

void printvalue(T (&a)[N])
{
    for(int i = 0; i != N; i++)
    {
        cout << a[i] << endl;
    }
}

int main(int argc, const char *argv[])
{
    int a[5] = {5, 4, 3, 2, 1};

    printvalue(a);
    return 0;
}
