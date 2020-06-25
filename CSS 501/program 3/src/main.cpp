/* File Name: main.cpp
 * Author name: Erika Parayno (SID #:1425156)
 * Date: November 12, 2019
 * How to use: Enter your sudoku when the program asks for input. Your sudoku should have 81 integers, should meet all
 * Sudoku constraints, and have at least one empty spot as indicated by a zero to perform solving algorithm. Special cases
 * should be handled smoothly and print corresponding error message.
 * Description: This class creates a new puzzle, prompts user for sudoku board, extracts 81 integers from user input to
 * put into empty 2d array of squares, and attempts to solve the Sudokou using a recursive algorithm with backtracking.
 * It prints out any errors or special cases. */

#include <iostream>
#include "Puzzle.h"

using namespace std;

int main() {
   Puzzle puzzle; // create a puzzle
   cout << "Message: Please enter your puzzle: " << endl;
   cin >> puzzle;   // Will extract the first 81 integers from user input and create a 2d array of properly constructed Squares.

   bool isValidStart = puzzle.validStartingBoard;
   cout << "Message: Your initial, reformatted board is: " << endl;
   cout << puzzle;

   if (isValidStart) {   // will attempt to solve if it was a valid starting board
      if (puzzle.solve(0,0)) {
         if (puzzle.size() > 0) {
            cout << "Message: Your SOLVED, reformatted board is: " << endl;
            cout << puzzle;
         } else {
            cout << "Message: Your board was already solved." << endl;
         }
      } else {
         cout << "Error: Your board was unsolvable."<< endl;   // if the solve function returned false
      }

   } else {
      cout << "Error: Your starting board contains values that do not meet Sudoku rules. The program did not attempt to solve your Sudoku." << endl;
   }

   return 0;
}