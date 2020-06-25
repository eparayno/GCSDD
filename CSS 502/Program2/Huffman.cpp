//------------------------------------------------------------------------
// CLASS: HUFFMAN.CPP
// Headerfile, containing defintions for functions for Huffman
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

#include "Huffman.h"
#include <iostream>

 //-------------------------------Constructor-------------------------------
 /*  Definition: Constructor for the Huffman class. Takes a frequency for
        each letter 'a' to 'z' and constructs a Huffman tree to compute a
        code for each character, which will be stored in the class codebook.
     Precondition: Must pass int[] that is size NUM_CHAR, which should be
        greater than 0.
     Post Condition: Generates codebook that accurately resembles the data
        stored in the Huffman tree. 
  */
Huffman::Huffman(int counts[NUM_CHAR]) {

    // create array of NodePtrs
    Node* ptrArray[NUM_CHAR];                   
    for (int i = 0; i < NUM_CHAR; i++) {
       ptrArray[i] = new Node();
       ptrArray[i]->frequency = counts[i];
       ptrArray[i]->letter = (char)((int)'a' + i);
    }

    // create a Heap by passing in array of NodePtrs
    Heap<Node> frequencies(ptrArray, NUM_CHAR);

    // create Huffman tree using Huffman algorithm
    while (frequencies.size() > 1) {
        Node* parent = new Node();

        parent->left = frequencies.deleteMin();
        parent->right = frequencies.deleteMin();
        
        parent->frequency = parent->right->frequency + parent->left->frequency;
        frequencies.insert(parent);
    }
    
    // extracts Huffman tree from Heap
    huffmanPtr = frequencies.deleteMin();

    // generates codebook from Huffman tree
    if (huffmanPtr != NULL) {
        string code = "";
        generateCodebook(huffmanPtr, code, 2);
    }
}

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
        frequency of 0, it will be represented as a "" in the array. */
void Huffman::generateCodebook(Node* subTree, string code, int direction){
    if (subTree->frequency > 0 && direction == 0) { //if we are visiting left child
        code += "0";
    }
    if (subTree->frequency > 0 && direction == 1) { //if we are visiting right child
        code += "1";
    }

    if (isalpha(subTree->letter)) {
        int locationInArray = (int)subTree->letter - (int)'a';
        if (subTree->frequency > 0) {
            codebook[locationInArray] = code;
        } else {
            codebook[locationInArray] = ""; // if the lettere has zero frequency, don't return a code.
        }
        return;
    }

    // continues to traverse down the tree and tracks code until it reaches letter.
    if (subTree->left != NULL) {
        generateCodebook(subTree->left, code, 0);
    }

    if (subTree->right != NULL) {
        generateCodebook(subTree->right, code, 1);
    }

}

//-------------------------------destructor------------------------------------
/*  Definition: Deallocates memory by passing in pointer to root of
        Huffman into recursive function, clear.
    Precondition: Will be called once Huffman is no longer within scope.
    Post Condition: Should successfully call clear, which deallocates
        and removes data from huffmanTree. */
Huffman::~Huffman() {
    clear(huffmanPtr);
}

//----------------------------------clear--------------------------------------
/*  Definition: Recursive method that traverses through the tree and 
        deallocates and removes data from HuffmanTree and its corresponding
        nodes.
    Precondition: Will be called by destructor. 
    Post Condition: All nodes dynamically allocated by Huffman should be
        deallocated and removed from memory. */
void Huffman::clear(Node*& subTree) {
    if (subTree == NULL)    {
        return;
    }

    // clears left subtree recursively
    if (subTree->left != NULL) {
        clear(subTree->left);
    }

    // clears right subtree recursively
    if (subTree->right != NULL) {
        clear(subTree->right);
    }
    
    // ensure everything is cleared
    subTree->frequency = NULL;
    subTree->letter = NULL;
    subTree->left = nullptr;
    subTree->right = nullptr;

    delete subTree;
    subTree = NULL;
}

//---------------------------------getWord-------------------------------------
/*  Definition: This methods takes in a word to encode. All letters in 
        the word are converted to the appropriate bit strings. Non-letters
        may be ignored.
    Precondition: Must pass in string with length greater than 0.
    Post Condition: Will return a summation of codes representing each
        character in the form of a string. */
string Huffman::getWord(string in) {
    string codeReturn;
    int s = in.size();
    for (int i = 0; i < s ; i++) {
        char c = in[i];
        int letterIndex = (int)c - (int)'a'; // calculates location of letter
        codeReturn += codebook[letterIndex];
    }
    return codeReturn;
}

//--------------------------------operator<<-----------------------------------
/*  Definition: Output the letter-to-code translation table with one 
        letter per line (in alphabetical order) followed by a space 
        and the binary encoding from the Huffman algorithm.
    Precondition: Codebook must be complete and accurately resbembles
        the data stored in Huffman. 
    Post Condition: Will print each letter along with its corresponding
        code (separated by endlines) onto cout. */
ostream& operator<<(ostream& output, Huffman& huffman) {
    int size = huffman.codebook->size();
    for (int i = 0; i < NUM_CHAR; i++) {
        char c = (char)((int)'a' + i);  // which letter this code represents
        output << c << ": " << huffman.codebook[i] << endl;
    }
    return output;
}



