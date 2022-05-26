// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// List Class Header File

#ifndef LIST_H
#define LIST_H
#include "Node.h"

class List
{

    protected:
        Node *head;
        Node *tail;

    public:
        List();
        List(string data);
        void addLast(string);
        void addFirst(string);
        string removeLast();
        string removeFirst();
        bool isEmpty() const;
        int size() const;
        virtual void print() const;
        friend ostream &operator<<(ostream&, const List&);
        virtual ~List();
};

#endif //LIST_H
