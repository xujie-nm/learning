#ifndef WORD_QR_H_
#define WORD_QR_H_

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)


class Word_qr
{
    public:
        Word_qr(std::string filename);

        int result(std::vector<std::string> &, int &);
        void set_word(std::string word);



    private:
        std::vector<std::string> lines_;
        std::map<std::string, int> words_;
        std::string word_;
        std::string filename_;

        int searchlines(std::vector<std::string> &);
        void tolines();
        void towords();
};

#endif  /*WORD_QR_H_*/
