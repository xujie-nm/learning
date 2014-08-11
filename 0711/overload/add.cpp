#include <iostream>
#include <string>
#include <vector>

using namespace std;

string add(const string &str1, const string &str2)
{
    return str1 + str2;
}

int add(int a, int b)
{
    return a + b;
}

int main(int argc, const char *argv[])
{
    string str1, str2;
    cout << "please input two strings" <<endl;
    cin >> str1 >> str2;
    cout << add(str1, str2) <<endl;
    int a , b;
    cout << "please input two ingters" << endl;
    cin >> a >> b;
    cout << add(a, b) <<endl;

    return 0;
}
