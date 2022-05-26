// Riley Ruckman, Travis Shields
// Project 4 - Classes
// ZombieList class and functions

#include "ZombieList.h"

//Constructor for ZombieList object
ZombieList::ZombieList()
{
    head = 0;
    graveyardHead = 0;
}

//Deconstructor for ZombieList object
ZombieList::~ZombieList()
{
    //dtor
}

// Adds a Zombie object to ZombieList
void ZombieList::add(Zombie *zombie)
{
    Zombie *zombPtr = zombie;
    // If there are no zombies in the ZombieList,
    // the added zombie is designated as the head.
    if (head == 0)
    {
        head = zombPtr;
        head->setNext(0);
    }
    // If there are Zombies in the ZombieList,
    // the last Zombie in the list is found and
    // set to follow the new zombie
    else
    {
        Zombie *curr = head;
        while (curr->getNext() != 0)
        {
            curr = curr->getNext();
        }
        curr->setNext(zombPtr);
    }

}

// Prints the contents of the Zombie List
 void ZombieList::printZombieRing()
{
    cout << "Zombie Ring:\n";
    Zombie *curr = head;
    // Prints pairs of following Zombie and followed Zombie
    while (curr->getNext() != 0)
    {
        cout << curr->getName()
            << " is following "
            << (curr->getNext())->getName()
            << endl;
        curr = curr->getNext();
    }
    // Prints last pair, where the last Zombie in the
    // ZombieList is following the head
    cout << curr->getName() << " is following "
        << head->getName() << endl;

}

// Processes request to kill a Zombie.
 void ZombieList::kill(string zombieName,const int altGame)
{
    // If the zombie with the given name is in the graveyard
    if(inGraveyard(zombieName))
    {
        cout << "Zombie " << zombieName
            << " is already in the grave\n"
            << endl;
    }
    // If the zombie with the given name is in the zombie ring
    else if(inZombieRing(zombieName))
    {
        Zombie *killed = head;
        // Finds zombie with given name in zombie ring
        while (killed->getName() != zombieName)
        {
            killed = killed->getNext();
        }
        Zombie *killer = head;
        // Creates Zombie object and locates the node before the curr Zombie
        while (killer->getNext() != killed && killer->getNext() != 0)
        {
            killer = killer->getNext();
        }

        // If the alternative game is being played and the years gone of the killer zombie
        // is more than the killed zombie, then nothing will happen. Otherwise,
        // the rest of the function will continue.
        if (altGame == 1 && (killer->getYears() > killed->getYears()))
        {
          cout << killed->getName() << " has rotted less and defended against "
            << killer->getName() << endl << endl;;
        }
        else
        {
            // Sets the target's killer to the found zombie in the step before
            killed->setKiller(killer);

            // If the target was the head of ZombieList, then the killer is technically
            // going after 0, since the last node points to 0. Since the last zombie's
            // target won't change, then the head of the ZombieList should change to the
            // target of the previous head, which should be the node the head is pointing to.
            // If the killed zombie was not the head, then the killer's next target is set to
            // the killed zombie's target.
            if (killed == head)
            {
                head = killed->getNext();
            }
            else
            {
                killer->setNext(killed->getNext());
            }

            cout << killer->getName() << " killed "
                << killed->getName() << endl << endl;

            // Adds killed zombie to graveyard
            // Same process as adding a zombie to the ZombieList
            // but head is replaced with graveyardHead.
            if (graveyardHead == 0)
            {
                graveyardHead = killed;
                killed->setNext(0);
            }
            else
            {
                // This process sets the current head of the graveyard
                // as the target of the newest addition to the graveyard
                // then sets the newest addition as head of graveyard.
                // This keeps the list functionality and allows newly-added
                // nodes to append to the front of the list.
                killed->setNext(graveyardHead);
                graveyardHead = killed;
            }
        }
    }
    // The given name was not found in either the graveyard or
    // the zombie ring
    else
    {
        cout << "No zombie found by that name\n"
            << endl;
    }
}

// Prints the contents of the graveyard
 void ZombieList::printGraveyard()
{
    cout << "\nGraveyard:\n";
    Zombie *curr = graveyardHead;
    while (curr != 0)
    {
        cout << curr->getName()
            << " killed by "
            << curr->getKiller()
            << endl;
        curr = curr->getNext();
    }
}

// Returns a True/False if a zombie with the given name exists
// in the zombie ring
bool ZombieList::inZombieRing(string zombieName)
{
    Zombie *curr = head;
    while (curr != 0)
    {
        if (curr->getName() == zombieName)
        {
            return 1;
        }
        curr = curr->getNext();
    }
    return 0;
}

// Returns a True/False if a zombie with the given name exists
// in the graveyard
bool ZombieList::inGraveyard(string zombieName)
{
    Zombie *curr = graveyardHead;
    while (curr != 0)
    {
        if (curr->getName() == zombieName)
        {
            return 1;
        }
        curr = curr->getNext();
    }
    return 0;
}

// Checks if the game is over
// The game is over when there is only one zombie left in the
// zombie ring. This is known when the head of the zombie ring
// isn't following another zombie
bool ZombieList::isGameOver()
{
    if (head->getNext() == 0)
    {
        cout << "\nGame Over!\nWinner is "
            << head->getName();
        printGraveyard();
        return 1;
    }
    else
    {
        return 0;
    }
}
