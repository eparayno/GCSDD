/* File Name: Puzzle.h
 * Author name: Erika Parayno (SID #:1425156)
 * Date: November 12, 2019
 * Description: This class contains all the declarations of methods in the Puzzle.cpp class. All methods are public
 * with the exception of the nested Square class, which is private and should only be accessed by the Puzzle class m
 * methods.
*/

#ifndef SUDOKUSOLVER_PUZZLE_H
#define SUDOKUSOLVER_PUZZLE_H
#include<iostream>

using namespace std;

class Puzzle{
private:
   /* File Name: Square.cpp
 * Author name: Erika Parayno (SID #:1425156)
 * Date: November 12, 2019
 * Description: This class contains all the declarations and definitions of member variables and methods in the Square class.
    * Each square contains an int value and boolean fixed. The following methods are used to set, modify, or access
    * member variables. Each square is placed into a specific x and y coordinate of the 2d array puzzle Sudoku board. */
   class Square {
   private:
      int value;
      bool fixed;

   public:
      /* Description: Default square constructor enters -1 as value by default.
       * Parameter: None.
       * Pre-condition: Will be called in the main. When the puzzle is created, you have 9x9 array of Squares.
       * Post-condition: This method will be responsible for setting each square to -1.
       * Return: N/A */
      Square() {
         value = -1;
      }

      /* Description: This method will take an inputValue and set it as value. Based on that value, it will determine
       * if it is a fixed or a variable value.
       * Parameter: const int& inputValue
       * Pre-condition: This is called in the cin>> operator, after it has extracted exactly 81 integers and is ready
       * to set the values of the 2d array.
       * Post-condition: It will update member class variable value and fixed.
       * Return: N/A */
      Square(const int& inputValue){
         value = inputValue;
         fixed = value != 0;
      }

      /* Description: Gets private class member variable int value
       * Parameter: N/A
       * Pre-condition: Will be called by Puzzle method get
       * Post-condition: Will get and return value
       * Return: Returns int value */
      int getValue() const {
         return value;
      }

      /* Description: Sets private class member variable int value
       * Parameter: const int& value
       * Pre-condition: Will be called by Puzzle method set
       * Post-condition: Will set value without checking whether or not it meets Sudoku rules
       * Return: N/A */
      void setValue(const int& value) {
         Square::value = value;
      }

      /* Description: Gets private class member variable bool fixed
       * Parameter: N/A
       * Pre-condition: This is called by Puzzle size method
       * Post-condition: Get boolean fixed and return it
       * Return: bool fixed */
      bool isFixed() const {
         return fixed;
      }
   };

public:
   static const int constraint = 9;
   Square puzzleBoard[constraint][constraint];
   bool validStartingBoard = true;

   /* Description: Default constructor for Puzzle.
    * Parameter: N/A.
    * Pre-condition: Will be called in the main prior to cin>> operator.
    * Post-condition: Creates default puzzle, which contains a constraint, 2d array size of constraint^(2), and validStartingBoard.
    * Return: N/A */
   Puzzle();

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
   friend istream &operator>>(istream &input, Puzzle& puzzle);

   /* Description: Overloaded cout<< operator that prints "human friendly" display of member variable 2d array puzzleBoard.
    * For a board with constraint value 9, this method will print a grid containing '|', '+', and '-' to separate 3 by 3
    * blocks.
    * Parameter: ostream &output and Puzzle puzzle.
    * Pre-condition: Will be called from main.
    * Post-condition: Uses a nested for loop to iterate through the board and will add special characters and strings at appropriate
    * coordinates to create separation between 3 by 3 blocks.
    * Return: N/A */
   friend ostream &operator<<(ostream &output, const Puzzle& puzzle);

   /* Description: Counts the number of variable entries in the board, which is also recognized as the number of 0's present
    * at the beginning of the game.
    * Parameter: N/A
    * Pre-condition: At the construction of each Square, isFixed must have been set to true if the int value was greater than
    * zero.
    * Post-condition: This will iterate through the board, and access each of the Square's isFixed member variable by calling
    * Square's method isFixed(). If it it return false, it will increment counter. Once it has accessed every Square of the
    * board, it will return the counter.
    * Return: int variableCounter which counts the number of false Square isFixed variables*/
   int size() const;

   /* Description: Takes coordinates and returns the value of the square in that location.
    * Parameter: const int&row and const int&col
    * Pre-condition: Called from main and accepts x and y coordinates. Coordinates must be less than constraint, since
    * we are using a zero-based array.
    * Post-condition: Will access Square located at particular coordinate, and call Square's getValue() method to return
    * the otherwise private int value in the Square class, which is nested in the Puzzle header file.
    * Return: Returns the Square's int value. */
   int get(const int& row, const int& col) const;

   /* Description: Will take coordinate values and tentative value. If the move is legal, it will set the value of square with
    * coordinates row and col to parameter value.
    * Parameter: const int& row, const int& col, int value
    * Pre-condition: Will be called with row and col less than constraint and int value. This will be mostly called in the
    * recursive method solve.
    * Post-condition: Will call isLegal(), passing in all three paramter values. If isLegal returns true, it will access the
    * Square of puzzleBoard at coordinates row and col, call its setValue() method, and update the Square's int value.
    * Return: If value was set, this method will return true. Otherwise, it will return false. */
   bool set(const int& row, const int& col, const int& value);

   /* Description: This method counts the number squares yet to be solved.
    * Parameter: N/A
    * Pre-condition: This will predominantly be called in the recursive function Solve. It plays as the base case of the method,
    * which stops the solving algorithm as soon as it detects that numEmpty is equal to zero, which means every square is
    * solved and contains legal values.
    * Post-condition: This method will iterate through each square, access Square int value, will increment counter if that
    * value is zero. At the end of this method, the counter should accurately depict the number of 0's (unsolved squares) still
    * present on the board.
    * Return: int emptyCounter */
   int numEmpty() const;

   /* Description: Checks to see if move (placement of parameter int value into row and col coordinates) is a valid move
    * and meets all three constraints that defines Sudoku.
    * Parameter: const int&row, const int& col, and const int& value
    * Pre-condition: This method is mostly called in the creation of board and during the recursive function. If it is not legal,
    * it will not continue to solving algorithm and  print an error.
    * Post-condition: This method will check if parameter int value already exists in parameter row, parameter col, and
    * the block in which row and col is located.
    * Return: If the move meets all three constraints, it will return true. Otherwise, it would have returned false before
    * it even reached the end of method*/
   bool isLegal(const int& row, const int& col, const int& value) const;

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
   bool solve(int row, int col);

};

#endif //SUDOKUSOLVER_PUZZLE_H
