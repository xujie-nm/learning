#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

int main(int argc, const char *argv[])
{
    int ival;
    while(cin >> ival, !cin.eof())
    {
        if(cin.bad())
            throw std::runtime_error("IO stream corrupted");
        if(cin.fail())
        {
            cerr << "bad data, try again" << endl;
            cin.clear();
            cin.ignore(numeric_limits <streamsize > ::max(), '\n');
            continue;
        }
        cout << ival <<endl;
    }
    return 0;
}
