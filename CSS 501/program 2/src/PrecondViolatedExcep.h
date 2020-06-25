// File Name: PrecondViolatedExcep.h
// Author name: Erika Parayno (SID: 1425156)
// Date: October 23, 2019
// Description: From Carrano and Henry's Data Abstraction and Problem Solving with C++ (6th edition).
// Created by Frank M. Carrano and Tim Henry.
// Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 7-5.
    @file PrecondViolatedExcep.h */

#ifndef _PRECOND_VIOLATED_EXCEP
#define _PRECOND_VIOLATED_EXCEP

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcep : public logic_error
{
public:
    PrecondViolatedExcep(const string& message = "");
}; // end PrecondViolatedExcep

#include "PrecondViolatedExcep.cpp"
#endif