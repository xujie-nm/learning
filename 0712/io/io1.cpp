#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[])
{
    ifstream is("test.txt");
    string word;
    vector<string> svec;
    while(is >> word)
    {
        svec.push_back(word);
    }

    for(auto &s:svec)
    {
        cout << s << " " ;
    }
    cout << endl;
    return 0;
}
