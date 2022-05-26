//
//  ZombieTest.cpp
//  ZombieProject
//
//  Created by mmuppa on 10/26/19.
//  Copyright © 2019 mmuppa. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include "Zombie.h"
#include "ZombieList.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <vector>
#include <algorithm>    // shuffle
using namespace std;
void playGame(ZombieList& zombieList,int);
void testHub();
void testGetName();
void testGetGender();
void testGetDeadYear();
void testGetReYear();
void testGetRank();
void testGetYears();
void testDisplayInfo();
void testSetNext();
void testGetNext();
void testSetKiller();
void testGetKiller();
void testAdd();
void testPrintZombieRing();
void testKill();
void testPrintGraveyard();
void testInZombieRing();
void testInGraveyard();
void testIsGameOver();

// random generator function:
int myRandom(int i) {
	return rand() % i;
}

int main(int argc, const char* argv[]) {
	cout << "Would you like to run the test functions? Yes(1), No(0)" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		testHub();
		return 0;
	}



	// For randomizing the names to use with the shuffle
	std::srand(unsigned(std::time(0)));
	fstream inputStream("zombienames.txt");
	char zombie[100];
	char* tokens;
	string tokensArray[6];
	vector<Zombie> zombieVector;
	while (!inputStream.eof()) {
		inputStream.getline(zombie, 100);
		// Tokenize the line to get the individual
		// zombie parameters
		tokens = strtok(zombie, " ");
		int i = 0;
		while (tokens != 0) {
			tokensArray[i] = tokens;
			// For testing
			// cout << tokensArray[i] << " ";
			tokens = strtok(NULL, " ");
			i++;
		}
		// cout << endl;
		// Construct the object with the parameters to
		// add to the vector object.
		string name = tokensArray[0];
		int gender = atoi(tokensArray[1].c_str());
		int deadYear = atoi(tokensArray[2].c_str());
		int reYear = atoi(tokensArray[3].c_str());
		int rank = atoi(tokensArray[4].c_str());
		int years = atoi(tokensArray[5].c_str());
		Zombie zombie(name, gender, deadYear, reYear, rank, years);
		zombieVector.push_back(zombie);
	}
	// Randomize the order of the objects
	random_shuffle(zombieVector.begin(), zombieVector.end(), myRandom);

	// Add the zombies to the list
	ZombieList zombieList;
	for (unsigned i = 0; i < zombieVector.size(); i++)
	{
		zombieList.add(&zombieVector.at(i));
	}

	int altGame;
	cout << "Do you want to play the alternative version of the game?";
	do
    {
        cout << "Please enter a 1 or 0";
        cin >> altGame;
    } while (altGame != 0 && altGame != 1);

	// Print once and play the game
	zombieList.printZombieRing();
	playGame(zombieList,altGame);

	inputStream.close();

	return 0;
}

// Play the game till it's over
void playGame(ZombieList& zombieList,int altGame) {
	do {
		string zombieName;
		cout << "\nEnter zombie to kill: ";
		cin >> zombieName;
		zombieList.kill(zombieName,altGame);
		zombieList.printZombieRing();
		zombieList.printGraveyard();
	} while (!zombieList.isGameOver());
}

//Calls all test functions and prints testing prompts
void testHub()
{
	cout << "\n--- Testing getName() --- \n";
	testGetName();
	cout << "\n--- Testing getGender() --- \n";
	testGetGender();
	cout << "\n--- Testing getDeadYear() --- \n";
	testGetDeadYear();
	cout << "\n--- Testing getReYear() --- \n";
	testGetReYear();
	cout << "\n--- Testing getRank() --- \n";
	testGetRank();
	cout << "\n--- Testing getYears() --- \n";
	testGetYears();
	cout << "\n--- Testing displayInfo() --- \n";
	testDisplayInfo();
	cout << "\n--- Testing setNext() --- \n";
	testSetNext();
	cout << "\n--- Testing getNext() --- \n";
	testGetNext();
	cout << "\n--- Testing setKiller() --- \n";
	testSetKiller();
	cout << "\n--- Testing getKiller() --- \n";
	testGetKiller();
	cout << "\n--- Testing add() --- \n";
	testAdd();
	cout << "\n--- Testing printZombieRing() --- \n";
	testPrintZombieRing();
	cout << "\n--- Testing kill() --- \n";
	testKill();
	cout << "\n--- Testing printGraveyard() --- \n";
	testPrintGraveyard();
	cout << "\n--- Testing inZombieRing() --- \n";
	testInZombieRing();
	cout << "\n--- Testing inGraveyard() --- \n";
	testInGraveyard();
	cout << "\n--- Testing isGameOver() --- \n";
	testIsGameOver();
	cout << "\n--- ALL TESTS COMPLETED --- \n";
}


//Zombie functions


//Creates a zombie and gets its name
void testGetName()
{
	cout << "-Initializing zombie with name Ricky- \n";
	Zombie zombie("Ricky", 0, 0, 0, 0, 0);
		cout << "Zombies name is " << zombie.getName() << endl;

}
//Creates a zombie and gets its gender
void testGetGender()
{
	cout << "-Initializing zombie with gender 1- \n";
	Zombie zombie("Ricky", 1, 0, 0, 0, 0);
	cout << "Zombies gender is " << zombie.getGender() << endl;
}
//Creates a zombie and gets its dead year
void testGetDeadYear()
{
	cout << "-Initializing zombie with deadYear 1951- \n";
	Zombie zombie("Ricky", 1, 1951, 0, 0, 0);
	cout << "Zombies gender is " << zombie.getDeadYear() << endl;
}
//Creates a zombie and gets its re year
void testGetReYear()
{
	cout << "-Initializing zombie with reYear 2002- \n";
	Zombie zombie("Ricky", 1, 1951, 2002, 0, 0);
	cout << "Zombies gender is " << zombie.getReYear() << endl;
}
//Creates a zombie and gets its rank
void testGetRank()
{
	cout << "-Initializing zombie with rank 57- \n";
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 0);
	cout << "Zombies gender is " << zombie.getRank() << endl;
}
//Creates a zombie and gets its years
void testGetYears()
{
	cout << "-Initializing zombie with years 102- \n";
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	cout << "Zombies gender is " << zombie.getYears() << endl;
}
// Creates a zombie object and displays its info
void testDisplayInfo()
{
    cout << "-Initializing zombie object- \n";
    Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
    zombie.displayInfo();

}

//Creates two zombies, sets next of first zombie to second zombie
void testSetNext()
{
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie* zombPtr = &zombie2;
	cout << "Adress of zombie2 is " << zombPtr << endl;
	zombie.setNext(zombPtr);
	cout << "zombie next set to " << zombie.getNext() << endl;

}
//Creates two zombies, sets next, and gets address of next
void testGetNext()
{
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie* zombPtr = &zombie2;
	cout << "Address of zombie2 is " << zombPtr << endl;
	zombie.setNext(zombPtr);
	cout << "zombie.getNext() holds value of " << zombie.getNext() << endl;
}
//Creates two zombies, sets zombie2 killer to zombie
void testSetKiller()
{
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie* zombPtr = &zombie;
	cout << "Name of killer is " << zombie.getName() << endl;
	zombie.setKiller(zombPtr);
	cout << zombie2.getName() << "'s killer set to " << zombie.getKiller() << endl;
}
//Creates two zombies, and gets address of killed zombies killer
void testGetKiller()
{
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie* zombPtr = &zombie;
	cout << "Name of killer is " << zombie.getName() << endl;
	zombie.setKiller(zombPtr);
	cout << zombie2.getName() << " was killed by " << zombie.getKiller() << endl;
}

// ZombieList functions

// Creates 3 zombies and adds them all to zombie ring
void testAdd()
{
	cout << "-Creating 3 Zombie objects to add to list- \n";
	ZombieList zombieList;
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie zombie3("Miguel", 1, 1812, 1912, 350, 195);
	zombieList.add(&zombie);
	zombieList.add(&zombie2);
	zombieList.add(&zombie3);
	cout << "Zombies successfuly added. \n";


}

//Creates 3 zombies, adds them to ring, and then prints ring
void testPrintZombieRing()
{
	cout << "-Creating 3 Zombie objects to add to list- \n";
	ZombieList zombieList;
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie zombie3("Miguel", 1, 1812, 1912, 350, 195);
	zombieList.add(&zombie);
	zombieList.add(&zombie2);
	zombieList.add(&zombie3);
	zombieList.printZombieRing();
}

//Creates 3 zombies, kills one, and then checks it cannot be killed again
void testKill()
{
	cout << "-Creating 3 Zombie objects to add to list- \n";
	ZombieList zombieList;
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie zombie3("Miguel", 1, 1812, 1912, 350, 195);
	zombieList.add(&zombie);
	zombieList.add(&zombie2);
	zombieList.add(&zombie3);
	cout << "Killing Ricky \n";
	zombieList.kill("Ricky");
	cout << "Trying to kill Ricky again \n";
	zombieList.kill("Ricky");

}

//Creates 3 zombies, kills 2, and then prints the graveyard
void testPrintGraveyard()
{
	cout << "-Creating 3 Zombie objects to add to list, then killing 2- \n";
	ZombieList zombieList;
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie zombie3("Miguel", 1, 1812, 1912, 350, 195);
	zombieList.add(&zombie);
	zombieList.add(&zombie2);
	zombieList.add(&zombie3);
	zombieList.kill("Ricky");
	zombieList.kill("Miguel");
	zombieList.printGraveyard();

}

//Creates 3 zombies, adds them to the ring, and then checks if they are in the ring
void testInZombieRing()
{
	cout << "-Creating 3 Zombie objects to add to list- \n";
	ZombieList zombieList;
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie zombie3("Miguel", 1, 1812, 1912, 350, 195);
	zombieList.add(&zombie);
	zombieList.add(&zombie2);
	zombieList.add(&zombie3);
	cout << "Checking if Ricky is in zombie ring \n";
		if (zombieList.inZombieRing("Ricky"))
		{
			cout << "Ricky is in the Zombie ring \n";
		}
		else {
			cout << "Ricky not found in Zombie ring \n";
		}
}
//Creates 3 zombies, adds them to the ring, kills one, and then checks if they are in the graveyard
void testInGraveyard()
{
	cout << "-Creating 3 Zombie objects to add to list- \n";
	ZombieList zombieList;
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	Zombie zombie2("Rachel", 0, 1918, 1995, 49, 75);
	Zombie zombie3("Miguel", 1, 1812, 1912, 350, 195);
	zombieList.add(&zombie);
	zombieList.add(&zombie2);
	zombieList.add(&zombie3);
	cout << "Killing Rachel \n";
	zombieList.kill("Rachel");

	cout << "Checking if Rachel is in Graveyard \n";
	if (zombieList.inGraveyard("Rachel"))
	{
		cout << "Rachel is in the Graveyard \n";
	}
	else {
		cout << "Rachel not found in Graveyard \n";
	}
}

// Creates a single zombie and adds to ring to test isGameOver function
void testIsGameOver()
{
	cout << "-Creating 1 Zombie object to declare winner \n";
	ZombieList zombieList;
	Zombie zombie("Ricky", 1, 1951, 2002, 57, 102);
	zombieList.add(&zombie);
	cout << "Checking if game is over \n";
	zombieList.isGameOver();
}








