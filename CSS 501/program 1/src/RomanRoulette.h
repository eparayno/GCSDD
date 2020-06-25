// File Name: RomanRoulette.h
// Author name: Erika Parayno
// Date: October 9, 2019
// Description: This file contains header files for all methods in RomanRoulette.cpp. All methods are used in main.

#ifndef PROGRAM1_ROMANROULETTE_H
#define PROGRAM1_ROMANROULETTE_H
#include <list>

using namespace std;

// Purpose: Accepts user inputs n and k to see if it meets requirements.
// Parameters: int n and int k
// Pre-condition: Called by main. Parameter requirements are n > 0 and k >= 0.
// Post-condition: The function will return a boolean value once it has completed.
// Return value: Will return true if values meet requirement and false if user entered illegal values.
// Functions called: N/a.
bool checkIfUserInputValid(int n, int k);

// Purpose: Accepts n to create list of size n (This will be the roulette)
// Parameters: int
// Pre-condition: Called by main, user input must be valid before this method can be called.
// Post-condition: This will create a list with values ascending from 1 to n.
// Return value: Will return list.
// Functions called: players.push_back(int i) from C++ STL Lists
list<int> initializeRoulette(int n);

// Purpose: Will accept a list of size n (roulette), iterate clockwise until it counts to the value of integer k
// (legal values of k >= 0), and perform a kill, reducing the list size by 1. To clarify, when k = 2, you are
// counting over two spots prior to next kill. After each kill, you will move one person to the
// right and count to k again to perform another killing. This cycle will continue until there is one person left
// in the circle (surviving player). It will return the surviving node.
// Parameters: list<int> list and int k
// Pre-condition: Called by main, is called after the Roulette has successfully initialized. The list should be of size
// n, with nodes ascending from 1 to n.
// Post-condition: This method will perform killing until one person is left in the list.
// Return value: This method will return the surviving node of the list.
// Functions called: list.begin(), list.end(), list.size(), and list.remove() from C++ STL lists
list<int> playGame(list<int> list, int k);

// Purpose: Will accept a list with only the surviving node and return its value (aka winning position).
// Parameters: list<int> list
// Pre-condition: The accepted list should be size of 1.
// Post-condition: It will extract the int value of the one node present in the list.
// Return value:  Will return an int value indicative of the winning position in the roulette game given n and k.
// Functions called: list.front() from C++ STL lists
int getSafePosition(list<int> list);

#endif

