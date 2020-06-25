// File Name: Node.h
// Author name: Erika Parayno (SID: 1425156)
// Date: October 23, 2019
// Description: Header file for Node.cpp and is from Carrano and Henry's Data Abstraction and Problem Solving with C++
// (6th edition). It contains private and public methods in Node.cpp. Two new methods along with 1 new class member
// variable added to add doubly linked list functionality.
// Created by Frank M. Carrano and Tim Henry.
// Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file Node.h
    Listing 4-1 */

#ifndef _NODE
#define _NODE

template<class ItemType>
class Node
{
private:
    ItemType        item; // A data item
    Node<ItemType>* next; // Pointer to next node
    Node<ItemType>* prev; // Pointer to prev node

public:
    Node();
    Node(const ItemType& anItem);
    Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
    void setItem(const ItemType& anItem);
    void setNext(Node<ItemType>* nextNodePtr);
    ItemType getItem() const ;
    Node<ItemType>* getNext() const ;

    // methods to add double linked list functionality
    /** Description: This method allows the user to traverse through the doubly linked list backwards (if desired).
    *  Parameter: None.
    *  Pre-condition: Must be called with exsiting node.
    *  Post-condition: It will get value of the previous node.
    *  Return: No return.
    */
    Node<ItemType>* getPrev() const;

    /** Description: This method sets the previous node pointer and points it to previous node.
    *  Parameter: Node<ItemType>* prevNodePtr
    *  Pre-condition: Must be called with existing node
    *  Post-condition: It will set current node's prev node pointer to previous node
    *  Return: No Return.
    * @tparam ItemType
    */
    void setPrev(Node<ItemType>* prevNodePtr);

}; // end Node

#include "Node.cpp"
#endif