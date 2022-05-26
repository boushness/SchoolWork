// Riley Ruckman, Travis Shields
// Project 4 - Classes
// Zombie class header file

#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <string>
#include <iostream>

using namespace std;

class Zombie
{
    public:
        Zombie(string, int, int, int, int, int);
        string getName() {return name;}
        int getGender() {return gender;}
        int getDeadYear() {return deadYear;}
        int getReYear() {return reYear;}
        int getRank() {return rank;}
        int getYears() {return years;}
        void displayInfo();
        string getKiller() {return killer;}
        Zombie* getNext() {return next;}
        void setNext(Zombie *);
        void setKiller(Zombie *);


        virtual ~Zombie();

    private:
        string name;
        int gender;
        int deadYear;
        int reYear;
        int rank;
        int years;
        Zombie *next;
        string killer;
};

#endif // ZOMBIE_H
