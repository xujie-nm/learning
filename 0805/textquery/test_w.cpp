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

    Word_qr ssw(filename);
    ssw.set_word(word);
    ssw.print();
    return 0;
}
