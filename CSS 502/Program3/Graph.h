//---------------------------------------------------------------------------
// GRAPH.H
// Header class containing declaration of Graph members. Also contains 
// nested structs EdgeNode, VertexNode, and Table, necessary for 
// functionality of Graph class.
// Authors:  Clark Olson
// Edited by: Erika Parayno (Student ID: 1425156)
//---------------------------------------------------------------------------
// Description: This graph class contains all members to create a Graph and
// calculate the shortest distance between two nodes using Dijkstra's 
// algorithm. The Graph is mostly represented by an array containing struct
// VertexNodes. Each node will contain a pointer to Vertex data and a 
// EdgeNode list that behaves much like a LinkedList. Each EdgeNode contains
// information about the src, the destination, and weight.  To keep track of
// shortest distances, we have a 2d array that contains Table. Each Table 
// contains information on src, dest, shortest distance so far, and whether
// or not it has been visited. These data is used to calculate shortest 
// distances.
// Assumptions:
//   -- Will be reading a txt file where the first line is the size
//   -- Will be reading a txt file where lines 1 - size are the string
//		locations that will be stored in Vertex data.
//	 -- Will be assuming anything past line size are edges to be stored in
//	    the Graph.
//   -- We using index 1 for all vertices
//	 -- Last line in the txt file will be 0, 0, 0 \n
//---------------------------------------------------------------------------

#include "Vertex.h"
#include <string>
#include <fstream>

class Graph {
public:
	// -------------------------------Default Constructor--------------------------
	// Description: Default constructor
	// Precondition: -- 
	// Postcondition: All members will contain intialized values define in header
	// Return: --
	Graph();

	// --------------------------------- Copy Constructor -------------------------
	// Description: A deep copy constructor
	// Precondition: Takes an existing Graph with size < MAX_VERTICES as parameter
	// Postcondition: This will contain same values as src for all members, but
	//		will contain different addresses, as it is a deep copy.			
	// Return: --
	Graph(const Graph& src);

	// ---------------------------------- Destructor ------------------------------
	// Description: Destructor that deallocates and removes all dynamically 
	//		allocated data. 
	// Precondition: Will be called once this is out of scope
	// Postcondition: All data will be deallocated and removed from memory. Can be
	//		verified by running on Valgrind or checking memory leaks.
	// Return: --
	~Graph();

	// ----------------------------------- Operator= ------------------------------
	// Description:	Will clear any existing data, copy items from parameter src,
	//		and return pointer to this. 
	// Precondition: Takes an existing Graph with size < MAX_VERTICES as parameter
	//		This will contain same values as src for all members, but will contain 
	//		different addresses, as it is a deep copy.	
	// Return: Returns this.
	Graph& operator=(const Graph& src);

	//-------------------------------- buildGraph ---------------------------------
	// Builds a graph by reading data from an ifstream
	// Preconditions:  infile has been successfully opened and the file contains
	//                 properly formated data (according to the program specs)
	// Postconditions: One graph is read from infile and stored in the object
	// Return: --
	void buildGraph(std::ifstream& infile);

	// --------------------------------- insertEdge -------------------------------
	// Description: This method will locate the VertexNode in the VertexNode[] by
	//		using the src number as index and add the new edge containing
	//		data passed in the paramater. If the EdgeNode already exists, it 
	//		will replace that node's existing weight. It uses basic linkedlist 
	//		insertion behavior.
	// Precondition: The vertexNode[] must have been initalized and src and dest 
	//		must be < MAX VERTICES 
	// Postcondition: New EdgeNode addeded onto VertexNode[]'s EdgeNode list if
	//		if it didn't already exist. If it already existed, weight was replaced.
	// Return: --
	void insertEdge(const int& src, const int& dest, const int& weight);

	// --------------------------------- removeEdge --------------------------------
	// Description: This will locate src VertexNode by using parameter src as index.
	//		It ill take that VertexNode's edgehead and traverse through it until
	//		it reaches the node with the same adjacentVertex and remove it. It will
	//		deallocate any data that was dynamically allocated. 
	// Precondition: An edge between src and destination should exist.
	// Postcondition: Removes the edge from Vertices and also updates shortest paths
	// Return: --
	void removeEdge(const int& src, const int& dest);

	// ------------------------------- findShortestPath ---------------------------
	// Description: Method that uses Graph data and implements Dijkstra's 
	//		algorithm to find the shortest path for each src and distance pair. 
	//		It uses Vertices[]'s EdgeNode list to extract src and dest data and add
	//		that into a Table. Dijkstra's algorithm is based on repeatedly 
	//		expanding the closest(determined by weight/ summation of weights) vertex 
	//		which has not yet been reached. It will continue until every Node is 
	//		visited for each src. This is achieved by using STL priority queue that
	//		prioritizes minimum values. 
	// Precondition: size must be > 0;
	// Postcondition: The shortest path will be stored in the T[][]. Each row in the
	//		2d array will represent a source, the column distance. Each Table will
	//		contain shortest calculated distance.
	// Return: --
	void findShortestPath();

	// ---------------------------------- displayAll ------------------------------
	// Description: Method that prints string location and all its possible 
	//		destinations with corresponding shortest distance and path. 
	//		Displayed in a labeled, formatted table. Because, this contains 
	//		printRow that takes a string address by parameter, it cannot be set 
	//		to const.
	// Precondition: In order to display the most up to date data, you must call
	//		findShortestDistance prior to this method being called.
	// Postcondition: Output a labeled, formatted table with shortest distance
	//		and path for each source and destination pair.
	// Return: --
	void displayAll();

	// ------------------------------------ display -------------------------------
	// Description: This will display the shortest distance and path from source
	//		and destination. It will also print out the locations you are visiting
	//		in the shortest path. Because, this contains printRow that takes a 
	//		string address by parameter, it cannot be set 
	//		to const.
	// Precondition: -- 
	// Postcondition: Will print src, dest, shortest path, shortest distance, and
	//		path locations onto cout. If it doesn't exist, path will be represent
	//		"--" and there will be no path locations.
	// Return: --
	void display(const int& src, const int& dest);

private:
	static const int MAX_VERTICES = 101;

	// can change to a class, if desired
	struct EdgeNode {					
		int adjVertex = 0;				// subscript of the adjacent vertex 
		int weight = 0;					// weight of edge
		EdgeNode* nextEdge = nullptr;
	};

	struct VertexNode {
		EdgeNode* edgeHead = nullptr;	// head of the list of edges
		Vertex* data = nullptr;			// store vertex data here
	};

	// array of VertexNodes
	VertexNode vertices[MAX_VERTICES];

	// table of information for Dijkstra's algorithm
	struct Table {
		int vertexID = 0;				// intialized as -1,
		int dist = INT_MAX;				// shortest known distance from source
		bool visited = false;			// whether vertex has been visited
		int path = 0;					// previous vertex in path of min dist
	};

	int size = 0;					// number of vertices in the graph
	Table T[MAX_VERTICES][MAX_VERTICES];
	// stores visited, distance, path -
	// two dimensional in order to solve
	// for all sources

	// ---------------------------------- clearItems -------------------------------
	// Description: This method will reset Table[][] values to intialized value,
	//		then it will proceed to clear data in the VertexNode[], which includes
	//		both data and EdgeNode list. It will call destructor of any item that
	//		was dynamically allocated to ensure the program runs free of memory 
	//		leaks. This clearItems is used for the destructor and also the 
	//		assignment operator=.
	// Precondition: Size should be greater than zero.
	// Postcondition: Will have reset/cleared values and deleted any data that
	//		was dynamically allocated. 
	void clearVertices();

	// ----------------------------------- copyItems ------------------------------
	// Description: Will copy all contents in VertexNode array and Table 2d array,
	//		through deep copy as well as size. 
	// Precondition: Will assume the Graph is empty and src size is < MAX_VERTICES
	//		This will only be called by the copy constructor and operator=.
	// Postcondition: Created new allocated data and copied all contents of Graph
	// Return: --
	void copyItems(const Graph& src);

	// ----------------------------- clearTableArray ------------------------------
	// Description: Clears all items in T[][] and resets them
	// Precondition: This will be called in the operator= and when a new node
	//		is removed.
	// Postcondition: All Tables in Table[][] will be reset to intialized values
	// Return: --
	void clearTableArray();

	// ---------------------------------- tracePath -------------------------------
	// Description: Recursive function that finds the shortest path by working
	//		backwards from the destination to the source. 
	// Precondition: It assumes that source and distance is not equal and that
	//		path is an empty string. 
	// Postcondition: Returns the path by updating the path parameter. 
	//		If there is no path, path will be an empty string.
	// Return: --
	void tracePath(const int& src, int& dest, std::string& path);

	// ----------------------------------- printRow -------------------------------
	// Description: This will print the source, destination, shortest distance, 
	//		and corresponding path in one line. 
	// Precondition: It assumes that source and distance is not equal and that
	//		path is an empty string. 
	// Postcondition: Src, dest, shortest distance, and path will be printed 
	//		to cout. If source is the destination, it will not print anything.
	//		If there is no path, it will print -- for distance.
	// Return: --
	void printRow(const int& src, int dest, std::string& path);
};
