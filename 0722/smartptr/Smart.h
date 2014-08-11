#ifndef SMART_H_
#define SMART_H_

#include <iostream>

class Animal
{
    public:
        Animal()
        {
            std::cout << "Animal" << std::endl;
        }
        ~Animal()
        {
            std::cout << "~Animal" << std::endl;
        }
};

class SmartPtr
{
    public:
        SmartPtr();
        explicit SmartPtr(Animal *ptr);
        ~SmartPtr();

        void resetPtr(Animal *ptr);
        const Animal *getPtr() const;

        Animal &operator*();
        const Animal &operator*() const;

        Animal *operator->();
        const Animal *operator->() const;

    private:
        SmartPtr(const SmartPtr&);
        void operator=(const SmartPtr &);
        Animal *ptr_;
};

#endif  /*SMART_H_*/
