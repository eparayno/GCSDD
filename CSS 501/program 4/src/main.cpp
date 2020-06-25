/* File name: main.cpp
 * Author name: Erika Parayno (SID #: 1425156)
 * Date: 11/27/2019
 * Description: This class is mostly responsible for reading both stopwords.txt and corpus. It will store stopwords.txt
 * in a vector array and will read the corpus with an array of size 11 that acts similar to a queue. It will create a
 * reading frame where index 0-4 are precontext, 5 is the key, and 6-11 are postcontext. It will add non-stop words into
 * the tree. The classes BST and LinkedList will take care of the rest. Then the main calls << on binary tree,
 * which will print the binary tree keys in alphabetical order and then its occurrences in chronological order, in
 * KWIC formatting.
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include "BST.h"

bool isStopWord(const string& key, vector<string> stopWords);
string getNextWord(ifstream &theFile, char x);
void shiftFrame(string (&readingFrame)[11]);
string refineKeyWord(string key);
void addContentsToTree(const string (&readingFrame)[11], BST &binaryTree, const vector<string> &stopWords);

int main(int argc, char* argv[]) {
   // will create vector array stopWords by extracting words from stopwords.txt
   vector<string> stopWords;
   string currStopWord;
   char c;
   ifstream stopwordsFile ("stopwords.txt");
   if (stopwordsFile.is_open()) {
      while ( stopwordsFile.good() ) {
         stopWords.push_back(getNextWord(stopwordsFile, c));
      }
      stopwordsFile.close();
   } else {
      cout << "could not open stopwords.txt file";    // prints error if not able to find / open stopwords.txt
   }

   string tentativeWordToBeAdded;
   if ( argc != 2) { // argc should be 2 for program to run
      cout << "usage: " << argv[0] << " <filename>\n";         // We print argv[0] assuming it is the program name.
   } else {
      ifstream theFile (argv[1]);   // We assume argv[1] is a filename to open
      if (!theFile.is_open()) {
         cout << "Could not open file\n";   // prints error if not able to open
      } else {
         BST binaryTree;   // initialize tree
         string readingFrame[11]; // initialize reading tree
         bool emptyArray = true;
         char x;

         while ( theFile.peek() && !theFile.eof()) {

            if (emptyArray) {
               // the contents of this if statement will manually fill a reading frame of size 11
               int counter = 0;
               while (counter < 5) {
                  readingFrame[counter] = " ";
                  counter++;
               }
               while (counter < 11) {   // fills the rest of array, starting at key.
                  string word = getNextWord(theFile, x);
                  if(word.length() > 0) {
                     readingFrame[counter] = word;
                     counter++;
                  }
               }
               emptyArray = false;   // changes this into false so it never enters this statement again

            } else {
               tentativeWordToBeAdded = getNextWord(theFile, x);

               if(tentativeWordToBeAdded.length() > 0) {
                  shiftFrame(readingFrame);   // shifts all contents to the left, leaving last frame spot empty
                  readingFrame[10] = tentativeWordToBeAdded;    // enters new word into last frame spot
               }
            }
            if (tentativeWordToBeAdded.length() > 0 || readingFrame[4] == " ") {
               addContentsToTree(readingFrame, binaryTree, stopWords);   // adds contents at current readingFrame
            }
         }

         int endCounter = 0;
         while (endCounter <= 5) {   // will add empty spaces to the last 5 spaces after the last word in file
            shiftFrame(readingFrame);
            readingFrame[10] = " ";
            addContentsToTree(readingFrame, binaryTree, stopWords);   // adds contents at current readingFrame
            endCounter++;
         }
         cout << binaryTree;   // prints binary tree in KWIC format
      }
   }
   return 0;
}

/* Description: takes a reading frame, extracts precontext, postcontext, and key, cleans up key as needed, and
 * passes it through BST add method to add all contents required for BSTNode.
 * Parameter: const string (&readingFrame)[11], BST &binaryTree, const vector<string> &stopWords
 * Pre-condition: called from main for each non-stopword in the corpus
 * Post-condition: added BSTNode onto tree with respective content
 * Return: N/A
 * */
void addContentsToTree(const string (&readingFrame)[11], BST &binaryTree, const vector<string> &stopWords) {
   string preContextInput;
   for (int i= 0 ; i < 5 ; i++) {
      preContextInput += readingFrame[i] + " ";
   }

   string postContextInput;
   for (int i = 6; i < 11; i++) {
      postContextInput += readingFrame[i] + " ";
   }

   string key = readingFrame[5];

   string keyRefined = refineKeyWord(key);
   if(!isStopWord(keyRefined, stopWords) && !keyRefined.empty()) {
      binaryTree.add(keyRefined, preContextInput, postContextInput);
   }
}

/* Description: takes a key and removes any leading or ending non alphabetical characters
 * Parameter: string key
 * Pre-condition: will be called prior to any time a key is added into the BST
 * Post-condition: beginning and end punction/ special characters will not be added to copy of key
 * Return: string keyRefined
 * */
string refineKeyWord(string key) {
   string keyRefined;
   for (int i = 0; i < key.size(); i++) {
      char currChar = key[i];
      if(i == 0 || i == key.size() - 1) {
         if(isalpha(key[i] - 0)) {
            keyRefined += currChar;
         }
      } else {
         keyRefined += currChar;
      }
   }
   return keyRefined;
}

/* Description: takes the reading frame array by reference and shifts all contents to the left by 1 position, leaving an
 * open slot at the ever end
 * Parameter: string (&readingFrame)[11]
 * Pre-condition: called from main after the previous key was added, so we can move on to next frame
 * Post-condition: successfully shifted all objects 1 position to left, leaving readingFrame[10] open for next word
 * Return: N/A
 * */
void shiftFrame(string (&readingFrame)[11]) {
   for (int i = 0; i < 10; i++) {
      readingFrame[i] = readingFrame[i + 1];
   }
}

/* Description: takes ifstream file and reads it by characters. while continue to add character onto string until
 * it reaches whitespace, and then it will return the new string.
 * Parameter: ifstream &theFile, char x)
 * Pre-condition: called in the main to read words from stopwords.txt and corpus
 * Post-condition: creates a word that is separated by whitespace
 * Return: string word
 * */
string getNextWord(ifstream &theFile, char x) {
   string word;
   while (((theFile.get(x)) && (!iswspace(x-0))) && (!theFile.eof())) {
      if (isalpha(x)) {
         if (isupper(x)){
            x = tolower(x-0);
         }
      }
      word += x;
   }
   return word;
}

/* Description: takes current word and vector of stopwords and checks if they match.
 * Parameter: const string& basicString,  vector<string> vector
 * Pre-condition: called by addWordsToTree. Will check if key is a stop word prior to adding to tree.
 * Post-condition: iterated through entire vector to check if the word matches with any of the stop words
 * Return: true if there's a match, false if not.
 * */
bool isStopWord(const string& key, vector<string> stopWords) {
   for(int i = 0 ; i < stopWords.size(); i++) {
      if (stopWords.at(i) == key) {
         return true;
      }
   }
   return false;
}

