#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[])
{
    ifstream in;
    in.open("test.txt");
    ofstream out;
    out.open("out.txt");
    string word;

    while(getline(in, word))
    {
        cout << word << endl;
        out << word << endl;
    }

    out.close();
    in.close();
    return 0;
}
