// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Stack Class Member Functions File

#include "Stack.h"

Stack :: Stack() : List() {}

Stack :: Stack(string name) : List(name) {}

void Stack :: push(string name)
{
    addFirst(name);
}

string Stack :: pop()
{
    if (head == NULL)
        throw "ERROR: No items in stack\n";
    else
        return removeFirst();
}

void Stack :: print() const
{
    Node *currentNode = head;
    cout << "Printing Stack: (Top to Bottom)\n";
    while(currentNode != NULL)
    {
        cout << currentNode->getData() << ", ";
        currentNode = currentNode->getNext();
    }
    cout << endl;
}

ostream &operator<<(ostream &output, const Stack &stack)
{
    Node *currentNode = stack.head;
    cout << "Printing Stack: (Top to Bottom)\n";
    while(currentNode != NULL)
    {
        output << currentNode->getData() << ", ";
        currentNode = currentNode->getNext();
    }
    output << endl;
    return output;
}
