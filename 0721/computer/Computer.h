#ifndef COMPUTER_H_
#define COMPUTER_H_

#include <iostream>
class Computer{
    public:
        Computer(){}
        virtual void price(){};
        virtual ~Computer(){};  
};

class Asus: public Computer
{
    public:
        Asus(){};
        void price()
        {
            std:: cout << 5000 << std::endl;
        }
        virtual ~Asus(){};
    private:
        
};

class Mac: public Computer
{
    public:
        Mac(){};
        void price()
        {
            std::cout << 10000 << std::endl;
        }
        virtual ~Mac(){};
    private:
        
};

class Dall:public Computer
{
    public:
        Dall(){};
        void price()
        {
            std::cout << 4000 << std::endl;
        }
        virtual ~Dall(){};
    private:
        
};

#endif  /*COMPUTER_H_*/
