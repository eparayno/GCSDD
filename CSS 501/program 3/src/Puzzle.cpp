/* File Name: Puzzle.cpp
 * Author name: Erika Parayno (SID #:1425156)
 * Date: November 12, 2019
 * Description: This class contains method definitions to construct, set and get member variables of Puzzle. It also
 * checks the validity of moves to ensure they follow Sudoku game constraints along with a solve method that utilizes
 * recursive backtracking to solve the constructed, valid board. There are two overloaded methods, operator>> and
 * operator<<. The operator>> extracts 81 integer values in a string of input and the operator<< prints a "human-friendly"
 * for user. */

#include <iosfwd>
#include <iostream>
#include <array>
#include "Puzzle.h"

using namespace std;

/* Description: Default constructor for Puzzle.
 * Parameter: N/A.
 * Pre-condition: Will be called in the main prior to cin>> operator.
 * Post-condition: Creates default puzzle as defined in header file.
 * Return: N/A */
Puzzle::Puzzle() = default;


/* Description: Overloaded stream input operator to read puzzles in a compact format, extract only integer values 0-9,
 * and create a new Sudoku puzzle board containing Squares with appropriate values.
 * Parameter: istream& input and Puzzle& puzzle.
 * Pre-condition: Takes in a string of input from main, which can contain numbers, letters, spaces, new line, and special characters.
 * Post-condition: This method will get string contents by character and will stop when it has collected constraint*constraint size of
 * integers in string variable type, which is the number of values required to create a full puzzle board. It will take each integer
 * value and use it to construct a new square. Using a nested for loop, that Square will be added to the puzzleBoard with
 * particular coordinates. This will repeat until it has created a full 2d array containing Squares with their own
 * respective int value and boolean isFixed member variables.
 * Return: N/A */
istream &operator>>(istream &input, Puzzle& puzzle) {
   char c;
   string numString = "";   // new string where integer values will be added

   bool reader = true;
   while (reader) {   // Will not reenter while loop once reader is false
      input.get(c);
      if (isdigit(c)) {   // will add character to string if it is a an integer between 0-9.
         numString += c;
      }
      if (numString.length() == (puzzle.constraint * puzzle.constraint)) {
         reader = false;   // reader is false once we reach the 81 integer mark
      }
   }

   int numStringIterator = 0;
   for (int row = 0; row < puzzle.constraint; ++row) {
      for (int col = 0; col < puzzle.constraint; ++col) {
         char charValue = numString[numStringIterator]; // Will iterate through string of 81 integers
         int value = charValue - '0'; // this converts char into int

         if (!puzzle.isLegal(row, col, value)) {
            /* This sets the boolean but continues to create the board regardless if the move is legal or not.
             * This is so that even if the program doesn't solve the board, it can print a "human-friendly" format
             * of the board. However, */
            puzzle.validStartingBoard = false;
         }

         Puzzle::Square s(value);   // create new square and pass the value, which will update value and fixed variables.
         puzzle.puzzleBoard[row][col] = s;   // adds the Square into the 2d array
         numStringIterator++;
      }
   }
}


/* Description: Overloaded cout<< operator that prints "human friendly" display of member variable 2d array puzzleBoard.
 * For a board with constraint value 9, this method will print a grid containing '|', '+', and '-' to separate 3 by 3
 * blocks.
 * Parameter: ostream &output and Puzzle puzzle.
 * Pre-condition: Will be called from main.
 * Post-condition: Uses a nested for loop to iterate through the board and will add special characters and strings at appropriate
 * coordinates to create separation between 3 by 3 blocks.
 * Return: N/A */
ostream &operator<<(ostream &output, const Puzzle& puzzle) {
   for (int row = 0; row < Puzzle::constraint; ++row) {
      for (int col = 0; col < Puzzle::constraint; ++col) {
         int currValue = puzzle.get(row, col);
         // The following if statements add special characters in particular columns to help separate 3x3 blocks
         if((col == 2) || (col == 5)) {
            output << currValue << "|";
         } else if (col == 8) {
            output << currValue << " " << endl;
         } else if (col == 0) {
            output << " " << currValue << " ";
         } else {
            output << currValue << " ";
         }
      }

      // The following if statements add special characters in particular rows to help separate 3x3 blocks
      if (row == 2 || row == 5) {
         output << "------+-----+------" << endl;
      }
   }
}


/* Description: Takes coordinates and returns the value of the square in that location.
 * Parameter: const int&row and const int&col
 * Pre-condition: Called from main and accepts x and y coordinates. Coordinates must be less than constraint, since
 * we are using a zero-based array.
 * Post-condition: Will access Square located at particular coordinate, and call Square's getValue() method to return
 * the otherwise private int value in the Square class, which is nested in the Puzzle header file.
 * Return: Returns the Square's int value. */
int Puzzle::get(const int &row, const int &col) const {
   int value = puzzleBoard[row][col].getValue();
   return value;
}


/* Description: Will take coordinate values and tentative value. If the move is legal, it will set the value of square with
 * coordinates row and col to parameter value.
 * Parameter: const int& row, const int& col, int value
 * Pre-condition: Will be called with row and col less than constraint and int value. This will be mostly called in the
 * recursive method solve.
 * Post-condition: Will call isLegal(), passing in all three paramter values. If isLegal returns true, it will access the
 * Square of puzzleBoard at coordinates row and col, call its setValue() method, and update the Square's int value.
 * Return: If value was set, this method will return true. Otherwise, it will return false. */
bool Puzzle::set(const int &row, const int &col, const int& value) {
   if (isLegal(row, col, value)) {   // prior to setting Square value, will check if move is legal
      puzzleBoard[row][col].setValue(value);   // if move is legal, it will set Square's value to paramater value
      return true;
   } else {
      return false;
   }
}


/* Description: Counts the number of variable entries in the board, which is also recognized as the number of 0's present
 * at the beginning of the game.
 * Parameter: N/A
 * Pre-condition: At the construction of each Square, isFixed must have been set to true if the int value was greater than
 * zero.
 * Post-condition: This will iterate through the board, and access each of the Square's isFixed member variable by calling
 * Square's method isFixed(). If it it return false, it will increment counter. Once it has accessed every Square of the
 * board, it will return the counter.
 * Return: int variableCounter which counts the number of false Square isFixed variables*/
int Puzzle::size() const{
   int variableCounter = 0;
   for (int rowIter = 0; rowIter < constraint; ++rowIter) {
      for (int colIter = 0; colIter < constraint; ++colIter) {
         if(!puzzleBoard[rowIter][colIter].isFixed()){
            // nested for loop iterates through entire board, will increment counter with each false isFixed Square found
            variableCounter++;
         }
      }
   }
   return variableCounter;
}


/* Description: This method counts the number squares yet to be solved.
 * Parameter: N/A
 * Pre-condition: This will predominantly called in the recursive function Solve. It plays as the base case of the method,
 * which stops the solving algorithm as soon as it detects that numEmpty is equal to zero, which means every square is
 * solved and contains legal values.
 * Post-condition: This method will iterate through each square, access Square int value, will increment counter if that
 * value is zero. At the end of this method, the counter should accurately depict the number of 0's (unsolved squares) still
 * present on the board.
 * Return: int emptyCounter */
int Puzzle::numEmpty() const {
   int emptyCounter = 0;
   for (int rowIter = 0; rowIter < constraint; ++rowIter) {
      for (int colIter = 0; colIter < constraint; ++colIter) {
         // nested for loop iterates through entire board, will increment counter with each Square containing value 0 found
         if(get(rowIter, colIter) == 0){
            emptyCounter++;
         }
      }
   }
   return emptyCounter;
}


/* Description: Checks to see if move (placement of parameter int value into row and col coordinates) is a valid move
 * and meets all three constraints that defines Sudoku.
 * Parameter: const int&row, const int& col, and const int& value
 * Pre-condition: This method is mostly called in the creation of board and during the recursive function. If it is not legal,
 * it will not continue to solving algorithm and  print an error.
 * Post-condition: This method will check if parameter int value already exists in parameter row, parameter col, and
 * the block in which row and col is located.
 * Return: If the move meets all three constraints, it will return true. Otherwise, it would have returned false before
 * it even reached the end of method*/
bool Puzzle::isLegal(const int &row, const int &col, const int &value) const {

   // checks row constraint
   for (int rowIterator = 0; rowIterator < constraint; rowIterator++) {
      int currValue = get(rowIterator, col);   // will only need one for loop as col is constant
      if ((currValue == value) && (value != 0)) {
         return false;
      }
   }

   // checks column constraint
   for (int colIterator = 0; colIterator < constraint; colIterator++) {
      int currValue = get(row, colIterator);   // will only need one for loop as row is constant
      if ((currValue == value) && (value != 0)) {
         return false;
      }
   }

   // checks block constraint
   int x,y; // following if statements determines start coordinates for 3x3 validation
   if (row < 3) {
      x = 0;
   } else if (row >= 3 && row < 6) {
      x = 3;
   } else {
      x = 6;
   }

   if (col < 3) {
      y = 0;
   } else if (col >= 3 && col < 6) {
      y = 3;
   } else {
      y = 6;
   }

   for (int i = x; i < (x + 3); i++) {
      for (int j = y; j < (y + 3); j++) {
         // will use a nested for loop since both row and col are changing.
         if ((puzzleBoard[i][j].getValue() == value) && (value != 0)) {
            return false;
         }
      }
   }

   // if it passed all three constraints, it will return true
   return true;
}


/* Description: Solves puzzle using recursive algorithm with backtracking until there are no unsolved squares left.
 * Parameter: int row and int col (not by reference)
 * Pre-condition: The very first call of this method will be from main and will start with row 0 and col 0. This ensures
 * that we are checking every spot on the 2d array as it is a row-major based array
 * Post-condition: This will check tentative values for int row and int col, if that tentative value is a legal move,
 * it will call itself (hence, recursive) to find the next zero and perform the same task. In the case that a later
 * attempt is not a valid move, it will return false, returning to previously found 0 and attempt a different value (hence
 * backtracking).
 * Return: If there are no zero's left, meaning the program has solved the puzzle, it will return true. Otherwise,
 * it will return false.*/
bool Puzzle::solve(int row,  int col) {

   if (numEmpty() == 0) {   // base case: will return true once all squares have values
      return true;
   }

   // while loop iterates through board, until next zero is found, incrementing row & col as it goes.
   while ((row < constraint) && (puzzleBoard[row][col].getValue() != 0)) {
      col++;
      if (col == constraint && row < constraint - 1) {
         row++;
         col = 0;
      }
   }

   // Will try values 1-9
   for (int tentativeValue = 1; tentativeValue <= 9; ++tentativeValue) {
      if (set(row, col, tentativeValue)) {   // if value is legal in given row, col, it will set row, col value to tentativeValue.
         if (solve(row, col)) {   // recursive call for next '0' values
            return true;   // will return true if success
         }
         set(row, col, 0);   // if no legal values exist for recursive call, it will set to 0 and try again.
      }
   }

   return false; // triggers backtracking
}

