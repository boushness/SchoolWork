// Riley Ruckman. Travis Shields
// Project 4 - Classes
// Zombie class and functions

#include "Zombie.h"
#include <iostream>

using namespace std;

// Constructor for Zombie object
Zombie::Zombie(string name, int gender, int deadYear, int reYear, int rank, int years)
{
this->name = name;
this->gender = gender;
this->deadYear = deadYear;
this->reYear = reYear;
this->rank = rank;
this->years = years;
this->next = 0;
}

// Deconstructor for Zombie object
Zombie::~Zombie()
{
    //dtor
}

// Sets the zombie that the current zombie is following
void Zombie::setNext(Zombie * zombPtr)
{
    this->next = zombPtr;

}

// Sets the killer of the current zombie
void Zombie::setKiller(Zombie * zomPtr)
{
    this->killer = zomPtr->getName();
}

// Displays the information for a Zombie object in a
// specific format
void Zombie::displayInfo()
{
    cout << "Name: " << name
        << "\nGender: " << (gender == 1?"M":"F")
        << "\nYear Departed: " << deadYear
        << "\nYear Reanimated: " << reYear
        << "\nCurrent Rank: " << rank
        << "\nYears Gone: " << years << endl;
}
