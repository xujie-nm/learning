#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<string> vec;
    vec.push_back("beijing");
    vec.push_back("tianjin");
    vec.push_back("shanghai");
    vec.push_back("chongqing");
    vec.push_back("shenzhen");
    for(auto &item: vec){
            cout << item << endl;
    }
    cout << endl;
    list<string> lst(vec.begin(), vec.end());
    for(auto &item: lst){
            cout << item << endl;
    }
    return 0;
}
