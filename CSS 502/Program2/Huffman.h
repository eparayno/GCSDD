//------------------------------------------------------------------------
// CLASS: HUFFMAN.H
// Headerfile, containing declarations for functions in Huffman.cpp file. 
// Also contains private struct Node which contains letter, frequency,
// along with right and left child pointers.
// Author:  Erika Parayno
//------------------------------------------------------------------------
// The Huffman class is constructed by passing an array of integers that 
//    hold frequency information (letter based on location and frequency
//    as the integer value). Each letter will be entered into a heap 
//    to produce a Huffman codebook which contains unique coding for 
//    each character. The user can call getWord to see the Huffman code
//    for a word by checking each character in the word, finding that 
//    character's corresponding code from the codebook, and adding all
//    codes together. 
//
// Assumptions:
//  - Assume integers passed contain integer values.
//  - Assume 26 represents 26 letters of alphabet (lowercase ASCII)
//------------------------------------------------------------------------

#pragma once
#include "Heap.h"
#include <string>

static const int NUM_CHAR = 26;

class Huffman {
public:

    //-------------------------------Constructor-------------------------------
     /*  Definition: Constructor for the Huffman class. Takes a frequency for
            each letter 'a' to 'z' and constructs a Huffman tree to compute a
            code for each character, which will be stored in the class codebook.
         Precondition: Must pass int[] that is size NUM_CHAR, which should be
            greater than 0.
         Post Condition: Generates codebook that accurately resembles the data
            stored in the Huffman tree.
      */
    Huffman(int counts[NUM_CHAR]);

    //-------------------------------destructor------------------------------------
    /*  Definition: Deallocates memory by passing in pointer to root of
            Huffman into recursive function, clear.
        Precondition: Will be called once Huffman is no longer within scope.
        Post Condition: Should successfully call clear, which deallocates
            and removes data from huffmanTree.
     */
    ~Huffman();

    //---------------------------------getWord---------------------------------
    /*  Definition: This methods takes in a word to encode. All letters in
            the word are converted to the appropriate bit strings. Non-letters
            may be ignored.
        Precondition: Must pass in string with length greater than 0.
        Post Condition: Will return a summation of codes representing each
            character in the form of a string.
     */
    string getWord(string in);

    //--------------------------------operator<<-------------------------------
    /*  Definition: Output the letter-to-code translation table with one
            letter per line (in alphabetical order) followed by a space
            and the binary encoding from the Huffman algorithm.
        Precondition: Codebook must be complete and accurately resbembles
            the data stored in Huffman.
        Post Condition: Will print each letter along with its corresponding
            code (separated by endlines) onto cout.
     */
    friend ostream& operator<<(ostream& output, Huffman& huffman);

private:
    //-------------------------------------------------------------------------
    // STRUCT NODE
    // Contains declaration and defintion of node struct. Also contains a 
    //      series of comparison operators.
    // A node will contain letter, frequency, and pointers to left and right
    //      children. 
    // Assumptions: None. 
    //-------------------------------------------------------------------------
    struct Node {
        char letter;
        int frequency;

        Node* left;
        Node* right;

        Node() {
            letter = '$';
            frequency = 0;
            left = nullptr;
            right = nullptr;
        }

        //--------------------------------operator<<-------------------------------
        /*  Definition: Comparison operator that checks if this node is less than 
                parameter node by comparing frequencies
            Precondition: None.
            Post Condition: Will return true if this is less than o */
        bool operator<(const Node& o) {
            return frequency < o.frequency;
        }

        //--------------------------------operator<<-------------------------------
        /*  Definition: Comparison operator that checks if this node is greater than
                parameter node by comparing frequencies
            Precondition: None.
            Post Condition: Will return true if this is greater than o */
        bool operator>(const Node& o) {
            return frequency > o.frequency;
        }

        //--------------------------------operator<<-------------------------------
        /*  Definition: Comparison operator that checks if this node is equal to
                parameter node by comparing frequencies
            Precondition: None.
            Post Condition: Will return true if this is equal to o */
        bool operator==(const Node& o) {
            return frequency = o.frequency;
        }

    };

    Node* huffmanPtr;                  // produced finalized heap product, huffmanPtr
    string codebook[NUM_CHAR];         // contains unique codes for each character

    //-----------------------------generateCodebook--------------------------------
    /*  Definition: Recursive method that allows for traversal through the
            Huffman tree to generate a unique string code composed of 0's
            (indicating left direction) and 1's (indicating right direction)
            for each character. The codes will be stored in codebook.
        Precondition: Must pass the root of the Huffman tree in order to
            properly traverse through entire tree. Will start with passing
            direction as 2, to avoid adding direction prior to entering the
            tree.
        Post Condition: The codebook will contain unique frequencies for
            letters with freqeuency greater than 0. If the letter has
            frequency of 0, it will be represented as a NULL cell in the
            array.
     */
    void generateCodebook(Node* subTree, string code, int direction);

    //----------------------------------clear----------------------------------
    /*  Definition: Recursive method that traverses through the tree and
            deallocates and removes data from HuffmanTree and its corresponding
            nodes.
        Precondition: Will be called by destructor.
        Post Condition: All nodes dynamically allocated by Huffman should be
            deallocated and removed from memory.
     */
    void clear(Node*& subTree);

};
