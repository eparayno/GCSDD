// File Name: PrecondViolatedExcep.cpp
// Author name: Erika Parayno (SID: 1425156)
// Date: October 23, 2019
// Description: From Carrano and Henry's Data Abstraction and Problem Solving with C++ (6th edition).
// Created by Frank M. Carrano and Tim Henry.
// Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 7-6.
    @file PrecondViolatedExcep.cpp */
#include "PrecondViolatedExcep.h"

PrecondViolatedExcep::PrecondViolatedExcep(const string& message): logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor

// End of implementation file.
