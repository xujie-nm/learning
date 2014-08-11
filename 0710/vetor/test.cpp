#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct _student {
    string name;
    int score;
    
}student;

int main(int argc, const char *argv[])
{
    vector<student> stuvec;
     student stu;
    string tname;
    int tscore;
    cout << "please input name score" <<endl;
    while(cin >> tname && cin >> tscore)
    {
        stu.name = tname;
        stu.score = tscore;
        stuvec.push_back(stu);
    }

    vector<string> namevec;
    int num = 0;
    for(vector<student>::iterator it = stuvec.begin(); it != stuvec.end(); ++it)
    {
        if((*it).score >= 60)
        {
            num++;
            namevec.push_back((*it).name);
        }
    }

//    cout << "begin end: " << stuvec.begin() << "  " << stuvec.end() << endl;
    cout << endl;
    cout << "the num is "<< num <<endl;
    cout << endl << "here is the passed list: " << endl;
    for(vector<string>::iterator ix = namevec.begin(); ix != namevec.end(); ++ix)
    {
        cout << *ix <<endl;
    }
    
    return 0;
}
