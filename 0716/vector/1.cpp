#include <iostream>
#include <string>
#include <vector>
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

    vector<string>::iterator res = find(vec.begin(), vec.end(), "tianjin");
    vec.insert(res, 3, "shenzhen");
    for(auto &item: vec){
            cout << item << endl;
    }

    return 0;
}
