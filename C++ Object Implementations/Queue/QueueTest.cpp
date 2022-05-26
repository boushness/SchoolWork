// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Test File for Queue Class

#include "Queue.h"

void testEnqueue();
void testDequeue();
void testQueuePrint();
void testQueueOstream();

int main()
{
    cout << "Testing Queue Class Member Functions\n";
    testEnqueue();
    testDequeue();
    //testQueuePrint();
    //testQueueOstream();

    return 0;
}

void testEnqueue()
{
    cout << "\nTesting Enqueue function of Stack class\n";
    Queue test("John");
    test.enqueue("Fred");
    cout << "Successfully added name to stack\n";
    test.print();
}

void testDequeue()
{
    cout << "\nTesting Dequeue function of Stack class\n";
    Queue test("John");
    test.enqueue("Fred");
    test.print();
    cout << "Successfully removed the first name, " << test.dequeue()
        << ", from the stack\n";
    test.print();
}

void testPrint()
{

}

void testQueueOstream()
{

}
