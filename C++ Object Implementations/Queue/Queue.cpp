// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Queue Class Member Functions File

#include "Queue.h"

Queue :: Queue() : List() {}

Queue :: Queue(string name) : List(name) {}

void Queue :: enqueue(const string &name)
{
    addLast(name);
}

string Queue :: dequeue()
{
    if (head == NULL)
        throw "ERROR: No items in queue\n";
    else
        return removeFirst();
}

void Queue :: print() const
{
    Node *currentNode = head;
    cout << "Printing Queue: (Front to Back)\n";
    while(currentNode != NULL)
    {
        cout << currentNode->getData() << ", ";
        currentNode = currentNode->getNext();
    }
    cout << endl;
}

ostream& operator<<(ostream &output, const Queue &queue)
{
    Node *currentNode = queue.head;
    cout << "Printing Queue: (Front to Back)\n";
    while(currentNode != NULL)
    {
        output << currentNode->getData() << ", ";
        currentNode = currentNode->getNext();
    }
    output << endl;
    return output;
}
