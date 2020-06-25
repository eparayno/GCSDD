//---------------------------------------------------------------------------
// VERTEX.H
// Header class containing declarations of Vertex class members.
// Authors: Erika Parayno (Student ID: 1425156)
//---------------------------------------------------------------------------
// Description: 
// This is just a simple class to store information associated with a Vertex. 
// In this assignment, it stores very little. However, the Graph class should
// not need to know the details of the what the Vertex stores. Because of
// this, the data is encapsulated as private member and the class contains
// setter and getter for retrieval and modifications
// Assumptions:
//   -- Each line in txt file from lines 1 to size will represent a Vertex
//	 -- rawData will store string data only
//---------------------------------------------------------------------------

#pragma once
#include <string>

class Vertex {
	std::string rawData;	// string data that records "location" of vertices

public:

	// --------------------------- Default Constructor ------------------------
	// Description: Default destructor sets rawData to empty string.
	// Precondition: -- 
	// Postcondition: Creates new Vertex with rawData initialized as ""
	Vertex();

	// ---------------------------------- getData -----------------------------
	// Description: Getter method for string rawData
	// Precondition: --
	// Postcondition: Returns private string rawData
	const std::string getData() const;

	// ---------------------------------- setData -----------------------------
	// Description: Setter method for string rawData
	// Precondition: Passed parameter must be existing string
	// Postcondition: RawData will be equal to string parameter
	const void setData(const std::string& location);
};

