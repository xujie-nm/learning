#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <typename T>

void swaptem1(T *a, T *b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
void swaptem2(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

int main(int argc, const char *argv[])
{
    int i = 1, j = 2;
    cout << "before"
    swap(&i, &j)
    return 0;
}
