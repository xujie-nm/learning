#include "word_qr.h"
using namespace std;

Word_qr::Word_qr(string filename)
    :filename_(filename)
{
    tolines();
    towords();
}

void Word_qr::tolines()
{
    ifstream is;
    is.open(filename_.c_str());
    //cout << is.good() << endl;

    string line;
    while(getline(is, line))
    {
        lines_.push_back(line);
        //cout << line << endl;
    }
}

void Word_qr::towords()
{
    ifstream is;
    is.open(filename_.c_str());

    string word;
    while(is >> word)
    {
        ++words_[word];
    }
}

int Word_qr::searchlines(vector<string> &vec)
{
    int linecount = 0;
    for(vector<string>::iterator it = lines_.begin(); 
        it != lines_.end(); ++it) 
    {
        string word;
        istringstream iss((*it));
        while(iss >> word)
        {
            if(word_ == word)
            {
                vec.push_back(*it);
                linecount++;
                break;
            }
        }
    }

    return linecount;
    
}

void Word_qr::set_word(string word)
{
    word_ = word;
}

int Word_qr::result(vector<string> &vec, int &linecount)
{
    linecount = searchlines(vec);
    if(linecount == 0)
    {     
        return  0;
    }
    return words_[word_] ;
}
