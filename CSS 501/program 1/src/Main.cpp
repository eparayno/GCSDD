// File Name: Main.cpp
// Author name: Erika Parayno
// Date: October 9, 2019
// Description: A group of people at size integer n (with legal values of n > 0) are arranged in a circle and are
// counted from 1 to n in a clockwise direction. The counting will continue until they have counted up to the value of
// integer k (legal values of k >= 0) and perform a kill, reducing the circle size by 1. To clarify,
// when k = 2, you are counting over two spots prior to next kill. After each kill, you will move one person to the
// right and count to k again to perform another killing. This cycle will continue until there is one person left
// in the circle, also known as the surviving player. The goal of this program is to return the
// winning person's number, thus locating safe position. To use this program, user must enter two integers n and k,
// following what constitutes legal values (n > 0 and k >= 0). The program will return 0 if n or k inputs don't meet
// requirements. Otherwise, valid input values will run game, print safe position value via iostream, and return 1.
// The program will be utilizing C++ STL lists. With a while loop, the program will redirect the pointer to the
// beginning of the list once it has iterated all the way to the end. This method will mimick the behavior of a
// circular linked list.


#include <iostream>
#include "RomanRoulette.cpp"

using namespace std;

// Purpose: The main is responsible for accepting and validating user inpuT, performing roulette game (given user
// entered legal values), printing safe position if existent.
// Parameters: N/a
// Pre-condition: N/a
// Post-condition: Played game until circle is reduced to size of 1, prints safe position (if existent).
// Return values: Method will return 0 if user entered invalid n or k. Otherwise, it will return safe position number.
// Functions called: checkIfUserInputValid(int n, k), intializeRoulette(int n), playGame(list<int> list, int k), 
// and getSafePosition(list<int> winner)
int main() {
   int n, k;
   cin >> n >> k;
   if (!checkIfUserInputValid(n, k)) {
      return 0; // If user input is invalid, program will return 0 and terminate.
   }

   list<int> players = initializeRoulette(n); // Will create circle (list) of size n.

   list<int> winner = playGame(players, k); // Will start at position 1 and perform killing as explained in description.

   int safePosition = getSafePosition(winner); // Will get number of surviving person (node).
   cout << safePosition << endl;

   return safePosition;
}


