#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    string s = "hello";
    string s1;
    cin >> s1;
    s = s + " ";
    s = s + s1;
    s = s + "!";
    string &s2;
    cout << s << endl << s2;
    return 0;
}
