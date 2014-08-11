#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int a, int b)
{
    return a < b;
}


int main(int argc, const char *argv[])
{
    vector<int> ivec;
    srand(10086);
    ivec.push_back(rand()%100);
    ivec.push_back(rand()%100);
    ivec.push_back(rand()%100);
    ivec.push_back(rand()%100);
    ivec.push_back(rand()%100);
    ivec.push_back(rand()%100);
    ivec.push_back(rand()%100);
    ivec.push_back(rand()%100);
    ivec.push_back(rand()%100);
    sort(ivec.begin(), ivec.end(), cmp);
    for(auto &it: ivec)
    {
        cout << it << " ";
    }
    cout << endl;
    return 0;
}

