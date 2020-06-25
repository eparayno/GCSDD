// File Name: main.cpp
// Author name: Erika Parayno (SID: 1425156)
// Date: October 23, 2019
// Description: This main is the driver. It's main function is to create two LinkedSortedList that is of size 50,
// and is composed of random integers between -9999 to 9999. It prints the contents of those lists and then
// calls merge sort to create a new list. The new list will contain every value from l1 and l2 in ascending order.
// We then deallocate the LinkedList, which can be checked with Valgrind.

#include <iostream>
#include "LinkedSortedList.h"
#include <random>

using namespace std;

// Purpose: Creates two linked lists to create another linked list that is a combination of values of original linked lists
// but also in order.
// Parameters: N/a
// Pre-condition: N/a
// Post-condition: 3 linked lists total created and the deallocated from memory.
// Return values: Method will return 0 if successful or precondviolated exception if failed.
// Functions called: insertSorted(), getEntry(), merge(), getLength().
int main() {
   // create number distribution for random number generator
   random_device chooser;
   mt19937 gen(chooser());
   uniform_int_distribution<> dis(-9999, 9999);

   // create 1st sorted list
   LinkedSortedList<int> list1;
   for (int i = 0; i < 50; i++) {
      int randomNum = dis(gen);     // generate random number
      list1.insertSorted(randomNum);   // insert that new random number into the list
   }
   cout << "Your list1 is: ";
   for (int i = 1; i <= list1.getLength(); i++)
   {
      cout <<  list1.getEntry(i) << " ";
   }
   cout << endl;


   // create 2nd sorted list
   LinkedSortedList<int> list2;
   for (int i = 0; i < 50; i++) {
      int randomNum = dis(gen);
      list2.insertSorted(randomNum);
   }
   cout << "Your list2 is: ";
   for (int i = 1; i <= list2.getLength(); i++)
   {
      cout <<  list2.getEntry(i) << " ";
   }
   cout << endl;

   //performing merge of two sorted lists
   LinkedSortedList<int>* productList = new LinkedSortedList<int>(list1.mergeSortedList(list2));


   //deallocating productList, should return no leaks in Valgrind
   productList->clear();
   delete productList;
   return 0;
}




