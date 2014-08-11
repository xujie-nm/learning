#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<int> vec(1);
    vec[0] = 3;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);

    for(auto &item: vec){
            cout << item << endl;
    }
    return 0;
}
