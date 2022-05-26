// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Test File for Node Class

#include "Node.h"

void testConstructor();
void testSetData();
void testSetNext();
void testSetPrev();
void testGetNext();
void testGetPrev();

int nodeMain()
{
    testConstructor();
    testSetData();
    testSetNext();
    testSetPrev();
    testGetNext();
    testGetPrev();

    return 0;
}

// Testing Node Constructor
void testConstructor()
{
    cout << "\nTesting constructor of Node class\n";
    Node node("apple");
    cout << "Node with data: " << node.getData() << endl;
}

// Testing Node set data
void testSetData()
{
    cout << "\nTesting setData function of Node class\n";
    Node node("apple");
    node.setData("apple");
    cout<<"Set Data-->"<<node.getData()<<endl;
    node.setData("Banana");
    cout<<"Set Data-->"<<node.getData()<<endl;
}

// testing node Set next
void testSetNext()
{
    cout << "\nTesting setNext function of Node class\n";
    Node node("Banana");
    node.setNext(&node);
    cout<<"Next data address-->"<<node.getNext()<<endl;
}

// Testing node set previous
void testSetPrev()
{
    cout << "\nTesting setPrev function of Node class\n";
    Node node("Apple");
    node.setPrev(&node);
    cout<<"Previous data Address-->"<<node.getPrev()<<endl;
}

// Testing Node get next
void testGetNext()
{
    cout << "\nTesting getNext function of Node class\n";
    Node node("Apple");
    cout<<" Get next successfully created: "<< node.getData()<<"<-->"<<node.getNext();
    cout<<endl;
}

//Testing node get previous
void testGetPrev()
{
    cout << "\nTesting getPrev function of Node class\n";
    Node node("Banana");
    cout<<" Get next successfully created: "<< node.getPrev()<<"<-->"<<node.getData();
    cout<<endl;
}
