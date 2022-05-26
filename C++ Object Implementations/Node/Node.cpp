// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Node Class Member Functions File

#include "Node.h"
#include <iostream>

Node::Node(string data)
{
    if (data.size() < 3)
    {
        throw "ERROR: name given is too small";
    }
    else if (data == "")
    {
        throw "ERROR: name cannot be nothing";
    }
    else
    {
        this->data = data;
        next = NULL;
        prev = NULL;
    }
}


