// Riley Ruckman, Travis Shields
// Project 4 - Classes
// ZombieList class header file

#ifndef ZOMBIELIST_H
#define ZOMBIELIST_H
#include "Zombie.h"
#include <iostream>
#include <string>

using namespace std;


class ZombieList
{
    public:
        ZombieList();
        void add(Zombie *);
        void printZombieRing();
        void kill(const string);
        void printGraveyard();
        bool inZombieRing(const string);
        bool inGraveyard(const string);
        bool isGameOver();

        virtual ~ZombieList();

    private:
        Zombie *head;
        Zombie *graveyardHead;
};

#endif // ZOMBIELIST_H
