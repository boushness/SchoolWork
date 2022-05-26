// Riley Ruckman, Surafel Seboka
// Project 5 - Inheritance
// Test File for Stack Class

#include "Stack.h"

void testPush();
void testPop();
void testPrint();
void testStackOstream();

int stackMain()
{
    return 0;
}

void testPush()
{
    cout << "Testing push function of Stack class\n";
    Stack test;
    test.push("apple");
    cout << "Successfully added name to stack\n";
    test.print();
}
