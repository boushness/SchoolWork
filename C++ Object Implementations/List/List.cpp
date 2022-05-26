// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// List Class Member Functions File

#include "List.h"

List :: List()
{
    head = NULL;
    tail = NULL;
}

List :: List(string data)
{
    Node *newNode = new Node(data);
    head = newNode;
    tail = newNode;
}

void List ::addLast(string data)
{
    Node *newNode = new Node(data);
    if (head == tail)
    {
        head->setNext(newNode);
        tail = newNode;
    }
    else if (tail != NULL)
    {
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    }
    else
    {
        head = newNode;
        tail = newNode;
    }
}

void List ::addFirst(string data)
{
    Node *newNode = new Node(data);
    if (head == tail)
    {
        tail->setPrev(newNode);
        head = newNode;
    }
    else if(head != NULL)
    {
        head->setPrev(newNode);
        newNode->setNext(head);
        head = newNode;
    }
    else
    {
       head = newNode;
       tail = newNode;
    }
}

string List ::removeLast()
{
    Node *deleteNode = tail;
    if(head == tail)
    {
        head = NULL;
        tail = NULL;
    }
    else
    {
        tail = deleteNode->getPrev();
        tail->setNext(NULL);
    }

    return deleteNode->getData();
}

string List ::removeFirst()
{
    Node *deleteNode = head;
    if(head == tail)
    {
        head = NULL;
        tail = NULL;
    }
    else
    {
        head = deleteNode->getNext();
        head->setPrev(NULL);
    }

    return deleteNode->getData();
}

bool List ::isEmpty() const
{
    return (head == NULL);
}

int List ::size() const
{
    Node *currentNode = head;
    int length = 0;
    while(currentNode != NULL)
    {
        length++;
        currentNode = currentNode->getNext();
    }
    return length;
}

void List :: print() const
{
    Node *currentNode = head;
    cout << "Printing List: (First to Last)\n";
    while(currentNode != NULL)
    {
        cout << currentNode->getData() << ", ";
        currentNode = currentNode->getNext();
    }
    cout << endl;
}

ostream &operator<<(ostream& output, const List& list)
{
    Node *currentNode = list.head;
    cout << "Printing List: (First to Last)\n";
    while(currentNode != NULL)
    {
        output << currentNode->getData() << ", ";
        currentNode = currentNode->getNext();
    }
    output << endl;
    return output;
}

List ::~List()
{
    Node* current = head;
    while(current != NULL )
    {
        Node *temp = current;
        current = current->getNext();
        delete temp;
    }

    head = NULL;
    tail = NULL;
}


