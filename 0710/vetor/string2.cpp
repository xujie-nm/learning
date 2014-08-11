#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<string> svec;
    string temp;
    while(cin >> temp)
    {
        for(string::iterator it = temp.begin(); it != temp.end(); ++it)
        {
            if(islower(*it))
            {
                *it = toupper(*it);
            }
            else if(isupper(*it))
            {
                *it = tolower(*it);
            }
        }

        svec.push_back(temp);
    }

    for(vector<string>::iterator ix = svec.begin(); ix != svec.end(); ++ix)
    {
        cout << *ix << " ";
    }

    cout << endl;
    return 0;
}
