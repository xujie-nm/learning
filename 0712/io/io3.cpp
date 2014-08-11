#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    int a;
    while(cin >> a)
    {
        cout << a << endl;
    }
    cout << "fail= " << cin.fail() << endl;
    cout << "eof= " << cin.eof() <<endl;
    
    cin.clear();
    cout << "after clear" <<endl;
    cout << "fail= " << cin.fail() << endl;
    cout << "eof= " << cin.eof() <<endl;
    
    string s = "hello world";
    cout << s << endl;
    return 0;
}
