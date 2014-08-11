#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    vector<string> svec;
    svec.push_back("hello ");
    svec.push_back("john ");
    svec.push_back("I ");
    svec.push_back("am ");
    svec.push_back("xujie ");
    //这是c++11的新标准，是从java借鉴过来的
    //auto自动识别 s 是 const string类型
    for(auto &s: svec)
    {
        cout << s << endl;
    }
    cout << endl;
    //auto自动识别 it 为 vector<string>::iterator 类型
    for(auto it = svec.begin(); it != svec.end(); ++it){
        cout << *it << endl  ;  
    }
    return 0;
}
