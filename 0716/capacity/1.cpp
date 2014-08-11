#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<int> vec;
    int i = 0;
    vec.resize(5);
    cout << "size: " << vec.size() << "    capacity: " << vec.capacity() << endl;
    while(1)
    {
        i++;
        vec.push_back(i);
        cout << "size: " << vec.size() << "    capacity: " << vec.capacity() << endl;
        sleep(1);
    }
    return 0;
}

