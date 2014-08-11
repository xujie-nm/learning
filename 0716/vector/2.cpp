#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class Test
{
    public:
        Test(){};
        Test(const Test &t){};
        Test& operator=(const Test& t){};
    private:
};

int main(int argc, const char *argv[])
{
    vector<string> vec;
    vec.push_back("beijing");
    vec.push_back("shanghai");
    vec.push_back("chongqing");
    vec.push_back("tianjin");

    vector<string>::iterator res = find(vec.begin(), vec.end(), "chongqing");
    vec.erase(res, vec.end());
    for(auto &item: vec){
            cout << item << endl;
    }

    cout << "-----------------" << endl;

    list<string> lst;
    lst.push_front("beijing");
    lst.push_front("shanghai");
    lst.push_front("chongqing");
    lst.push_front("tianjin");

    for(auto &item: lst){
        cout << item << endl;
    }
    return 0;
}
