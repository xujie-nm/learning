#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    vector<string> svec;
    cout << "the size of svec is " << svec.size() << endl;
    string temp;
    while(cin >> temp)
    {
        svec.push_back(temp);
    }
    cout << endl;
 /*  svec.push_back("I ");
    svec.push_back("am ");
    svec.push_back("xujie ");
    svec.push_back("hello! ");
*/
    cout << "the size of svec is " << svec.size() << endl;
    for(vector<string>::iterator it = svec.begin(); it != svec.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;
   
    return 0;
}
