// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Stack Class Header File

#ifndef STACK_H
#define STACK_H
#include "List.h"
#include <iostream>

class Stack : public List
{
    public:
        Stack();
        Stack(string);
        void push(string);
        string pop();
        void print() const;
        friend ostream &operator<<(ostream&,const Stack&);
};

#endif // STACK_H
