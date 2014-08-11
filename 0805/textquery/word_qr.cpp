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

    string line;
    while(getline(is, line))
    {
        lines_.push_back(line);
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

int Word_qr::searchlines()
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
                cout << *it << endl;
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

void Word_qr::print()
{
    int linecount;
    linecount = searchlines();
    cout << endl;
    cout << endl;
    cout << "the line count : " << linecount << endl;
    if(linecount == 0)
    {     
        cout << "the word count :  0" << endl;
        return ;
    }
    cout << "the word count : " << words_[word_] << endl;
}
