// File Name: Node.cpp
// Author name: Erika Parayno (SID: 1425156)
// Date: October 23, 2019
// Description: Implementation file for Node class and is from Carrano and Henry's Data Abstraction and Problem Solving with C++
// (6th edition). It contains private and public methods in Node.cpp. Two new methods along with 1 new class member
// variable added to add doubly linked list functionality.
// Created by Frank M. Carrano and Tim Henry.
// Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file Node.cpp
    Listing 4-2 */
#include "Node.h"
#include <cstddef>

template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
        item(anItem), next(nextNodePtr)
{
} // end constructor

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
   item = anItem;
} // end setItem

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
   next = nextNodePtr;
} // end setNext

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
   return item;
} // end getItem

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
   return next;
} // end getNext


// the following methods are specific to doubly linked list functionality
/** Description: This method allows the user to traverse through the doubly linked list backwards.
 *  Parameter: None.
 *  Pre-condition: Must be called with exsiting node.
 *  Post-condition: It will get value of the previous node.
 *  Return: No return.
 */
template<class ItemType>
Node<ItemType>* Node<ItemType>::getPrev() const
{
   return prev;
} // end getPrev

/** Description: This method sets the previous node pointer and points it to previous node.
 *  Parameter: Node<ItemType>* prevNodePtr
 *  Pre-condition: Must be called with existing node
 *  Post-condition: It will set current node's prev node pointer to previous node
 *  Return: No Return.
 * @tparam ItemType
 */
template<class ItemType>
void Node<ItemType>::setPrev(Node<ItemType>* prevNodePtr)
{
   prev = prevNodePtr;
} // end setNext
