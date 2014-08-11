#include "word_qr.h"
using namespace std;

int main(int argc, const char *argv[])
{
//    string filename(argv[2]);
//    string word(argv[3]);
   
    string filename;
    string word;

    cout << "input a filename" << endl;
    cin >> filename;

    cout << "input a word" << endl;
    cin >> word;

    vector<string> lines;
    int linecount;
    int wordcount;

    Word_qr ssw(filename);
    ssw.set_word(word);
    wordcount = ssw.result(lines, linecount);

    for(vector<string>::iterator it = lines.begin(); it != lines.end(); ++it){
        cout << *it << endl;    
    }

    cout << "the word count is " << wordcount << endl;
    cout << "the line count is " << linecount << endl;
    return 0;
}
