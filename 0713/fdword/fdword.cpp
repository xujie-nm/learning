#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Word
{
    string word;
    int times;
};

bool sub(const string &w1, const string &w2)
{
    if(w1.size() == w2.size())
    {
        return w1 == w2;
    }
    int i = 0;
    while(i != w2.size())
    {
        if(w1[i] != w2[i])
            return false;
        i++;
    }
    return true;
}

void push(vector<Word> &wvec, string word)
{
    vector<Word>:: iterator it;
    for(it = wvec.begin(); it != wvec.end(); ++it){
        if(it->word ==  word)
        {
             ++(it->times);
             break;
        }
    }
    if(it == wvec.end())
    { 
        Word w1;
        w1.word = word;
        w1.times = 1;
        wvec.push_back(w1);
    }
}

int main(int argc, const char *argv[])
{
    ifstream is("test.txt");
    vector<Word> wvec;
    string ww;
    while(is >> ww)
    {
        push(wvec, ww);
    }

    for(auto &s:wvec)
    {
        cout << s.word << endl;
        cout << s.times << endl;
    }

    cout << "please input the word" << endl;
    string ww1;
    cin >> ww1;
    cout << ww1 << endl;
    vector<Word>::iterator it;
    for( it = wvec.begin(); it != wvec.end(); ++it){
            if(sub(it->word, ww1))
            {
                cout << ww1 <<endl;
                cout << "word: " << it->word << endl;
                cout << "times: " << it->times << endl;
               // break;
            }
    }
 //   if(it == wvec.end())
 //      cout << "do not have this" << endl;
    return 0;
}
