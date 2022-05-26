// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Queue Class Header File

#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"
#include <iostream>

class Queue : public List {
    public:
        Queue();
        Queue(string);
        void enqueue(const string &);
        string dequeue();
        virtual void print() const;
        friend ostream& operator<<(ostream &, const Queue &);
};

#endif // QUEUE_H
