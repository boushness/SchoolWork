// Riley Ruckman, Surafel Sebokav
// Project 5 - Inheritance
// Node Class Header File

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>

using namespace std;

class Node
{

    private:
        string data;
        Node *prev;
        Node *next;

    public:
        Node(string data);
        string getData() const
        {return data;}
        void setData(const string &data)
        {this->data = data;}
        Node *getNext()
        {return next;}
        Node *getPrev()
        {return prev;}
        void setNext(Node *n)
        {next = n;}
        void setPrev(Node *p)
        {prev = p;}
};

#endif // NODE_H
