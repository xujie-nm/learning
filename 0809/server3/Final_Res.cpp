#include "Final_Res.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <echo/Exception.h>
using namespace std;

Final_Res::Final_Res(const string &filename)
    :query_(filename)
{
    timer.setTimer(3, 3);
    timer.setTimerCallback(bind(&Final_Res::write_cache, this));
    timer.startTimerThread();
}

int Final_Res::LCS(const string &tword, const string &word_)
{
    int n = word_.size();
    int m = tword.size();
    int num[n + 1][m + 1];
    
    for (int i = 0; i <= n; i++) 
    {
        num[i][0] = 100;    
    }

    for (int j = 0; j <= m; j++) 
    {
        num[0][j] = 100;    
    }
    num[0][0] = 0;

    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= m; j++) 
        {
            if(word_[i - 1] == tword[j - 1]) 
            {
                num[i][j] = num[i - 1][j - 1];
            }
            else
            {
                int a1 = num[i][j - 1];
                int a2 = num[i - 1][j];
                int a3 = num[i - 1][j - 1];
                num[i][j] = Min(a1, a2, a3) + 1;
            }
        }    
    }


    return num[n][m];
}

int Final_Res::Min(int a1, int a2, int a3)
{
    if(a1 < a2)
    {
        if(a1 < a3)
            return a1;
        else
            return a3;
    }
    else
    {
        if(a2 < a3)
            return a2;
        else
            return a3;
    }
}

string Final_Res::runLCS(const string &word)
{
    res_.clear();
    //test
    cout << word << endl;
    //test
    //cout << "ok" << endl;
    string ff = find_in_cache(word);

    //cout << "ok1" << endl;
    if( ff.size() != 0)
    {
        return ff;
    }
    else
    {
        wordMap_ = query_.get_word_map();

        map<string, set<LineNo> >::iterator ix;
        ix = wordMap_.find(word);
    
        if(ix == wordMap_.end())
        {
            //test
            //cout << "ok2" << endl;
            //test
            for(map<string, set<LineNo> >::iterator it = wordMap_.begin(); it != wordMap_.end(); ++it)
            {
                if(int ll = LCS(it->first, word) < 3) 
                    res_.insert(make_pair(it->first, make_pair(it->second.size(), ll)));
            }

            //test
            ///cout << "ok3" << endl;
            //test

            if(res_.empty())
                return string("search failed");
        
            string final = find();

            //test
            //cout << "ok4" << endl;
            //test
            string test = final;
            cout << test << endl;
            // sleep(3);
            //test
            final = query_.runQuery(final);
            final += string("\n") + string("the search word: ") + test + string("\n");
            //in here
            cache_.insert(make_pair(word, final));
            //test
            //cout << "ok5" << endl;
            //test
            return final;
        }
        else
        {
            string res = query_.runQuery(word);
            cache_.insert(make_pair(word, res));
            return res;
        }
    }
}

string Final_Res::find()
{
   string final; 
   int ll = 3;
        for(map<string, pair<int, int > >::iterator it = res_.begin(); it != res_.end(); ++it)
        {
            if(it->second.second < ll)
            {
                ll = it->second.second;
                //test
               // cout << it->first << "  " << it->second.first << "  " << it->second.second << endl;
                //test
            }
        }

   int freq = 0;
        for(map<string, pair<int, int> >::iterator it = res_.begin(); it != res_.end(); ++it)
        {
            if(it->second.second == ll && it->second.first > freq ) 
            {
                //test
                //cout << it->first << "  " << it->second.first << "  " << it->second.second << endl;
                //test
                freq = it->second.first;
                final = it->first;
            }
        }

        return final;
}


string Final_Res::find_in_cache(const string &word)
{
    map<string, string>::iterator it = cache_.find(word);

    //cout << " in cache" << endl;

    if(it == cache_.end())
        return string("");
    else
        return it->second;
}

void Final_Res::write_cache()
{
    ofstream fos;
    fos.open("cache.txt", ofstream::app);

    if(!fos)
        throw Exception("write open file fail!!");

    for(map<string, string>::iterator it = cache_.begin(); it != cache_.end(); ++it)
    {
        fos << it->first << " " << it->second << endl;        
    }
}
