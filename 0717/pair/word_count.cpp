#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

int main(int argc, const char *argv[])
{
    set<string> set1;
    string word2;
    cout << "please input the word do not count" << endl;
    while(cin >> word2)
    {
        set1.insert(word2);
    }
    cin.clear();
    map<string, int> words;
    string word;
    cout << "please input tne count word" << endl;
    while(cin >> word)
    {
//        if (word == string("end"))
//            break;
        if(set1.count(word) == 1)
            continue;
        ++words[word];
    }
    for(map<string, int>::iterator it = words.begin(); it != words.end(); ++it){
        cout << it->first << "  " << it->second << endl;    
    }
    string word1;
    cout << "please input the word you want to know" << endl;
    cin.clear();
    while(cin >> word1)
    {
        map<string, int>::iterator res = words.find(word1);
        if(res == words.end())
        {
            cout << "not found" << endl;
        }else
        {
            cout << res->first << " " << res->second << endl;
        }
    }
    return 0;
}
