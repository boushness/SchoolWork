// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Test File for List Class

#include "List.h"

void testDefaultConstructor();
void testOverloadConstructor();
void testAddLast();
void testAddFirst();
void testRemoveLast();
void testRemoveFirst();
void testIsEmpty();
void testOstream();


int listMain()
{
    testDefaultConstructor();
    testAddLast();
    testAddFirst();
    testRemoveLast();
    testRemoveFirst();
    testIsEmpty();
    testOstream();

    return 0;
}

// Testing default List Constructor
void testDefaultConstructor()
{
    cout<<"\nTesting Default List Constructor"<<endl;
    List list;
    cout <<"Successfully created a List object" << endl;
}

// Testing overloaded List Constructor
void testOverloadCosntructor()
{
    cout<<"\nTesting overloaded List Constructor"<<endl;
    List list("Bryan");
    cout <<"Successfully created a List object" << endl;
}

// Testing list add last
void testAddLast()
{
    cout<<"\nTesting Adding last"<<endl;
    List list;
    list.addLast("Seboka");
    list.print();
    cout <<"Successfully created add last" <<endl;
}

// Testing list add first
void testAddFirst()
{
    cout<<"\nTesting adding first"<<endl;
    List list;
    list.addFirst("surafel");
    list.print();
    cout <<"Successfully created add first"<<endl;
}

// Testing remove last
void testRemoveLast()
{
    cout<<"\nTesting remove last"<<endl;
    List list("seboka");
    string removedLast = list.removeLast();
    cout<<"removed from an empty list:" <<removedLast
        <<endl;
}

// Testing list remove first
void testRemoveFirst()
{

    cout<<"\nTesting remove first"<<endl;
    List list("surafel");
    string removedFirst = list.removeFirst();
    cout<<"removed from an empty list:" <<removedFirst
        <<endl;
}

// Testing list is empty
void testIsEmpty()
{
    List list;
    cout<<"If a list is empty (True=1)or (False=0)"<<endl;
    cout<< list.isEmpty()<<endl;
    list.addFirst("surafel");
    cout<< list.isEmpty()<<endl;
    list.removeFirst();
    cout<<"check an empty list:"
        <<endl;
    cout<< list.isEmpty()<<endl;
}

// Testing list friend ostream
void testOstream()
{
    List list("Happy");
    cout<<"List of friend ostream-->"<<list<<endl;
}
