#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
using namespace std;

class WordCount
{
    public:
        WordCount(const string &filename):filename_(filename){
              readtoset();
        }

        void add(const string &word)
        {
             if(set_.count(word) == 0)
             {
                 ++map_[word];
             }
        }

        void print()const
        {
            for(map<string, int>::const_iterator it = map_.begin(); it != map_.end(); ++it){
                cout << it->first << "  " << it->second << endl;    
           }

        }

    private:
        void readtoset()
        {
            ifstream in(filename_.c_str());
            string word;
            while(in >> word)
            {
                set_.insert(word);
            }
        }
        map<string, int> map_;
        set<string> set_;
        string filename_;
};

int main(int argc, const char *argv[])
{
    WordCount w1("word.txt");
    w1.add("a");
    w1.add("apple");
    w1.add("is");
    w1.add("here");
    w1.add("the");
    w1.add("shit");
    w1.add("smell");
    w1.add("really");
    w1.add("bad");

    w1.print();

    return 0;
}
