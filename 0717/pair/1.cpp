#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<pair<string, int> > vec;
    string p1; int p2;
    while(cin >> p1 >> p2)
    {
        vec.push_back(make_pair(p1, p2));
    }

    for(vector<pair<string, int> >::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << it->first << "  " << it->second << endl;    
    }
    return 0;
}
