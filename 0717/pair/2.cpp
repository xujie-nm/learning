#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(int argc, const char *argv[])
{
    map<string, int> m1;
    m1["bejing"] = 31;
    m1["shanghai"] = 32;
    m1["tianjin"] = 28;
    m1["chongqin"] = 35;

    for(map<string, int>::iterator it = m1.begin(); it != m1.end(); ++it){
        cout << it->first << "  " << it->second << endl;    
    }
    return 0;
}
