//---------------------------------------------------------------------------
// GRAPH.CPP
// CPP class containing definitions of Graph class members.
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

#include <fstream>

#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// -------------------------------Default Constructor--------------------------
// Description: Default constructor
// Precondition: -- 
// Postcondition: All members will contain intialized values define in header
// Return: --
Graph::Graph() {}

// --------------------------------- Copy Constructor -------------------------
// Description: A deep copy constructor
// Precondition: Takes an existing Graph with size < MAX_VERTICES as parameter
// Postcondition: This will contain same values as src for all members, but
//		will contain different addresses, as it is a deep copy.			
// Return: --
Graph::Graph(const Graph& src) {
	copyItems(src);
}

// ---------------------------------- Destructor ------------------------------
// Description: Destructor that deallocates and removes all dynamically 
//		allocated data. 
// Precondition: Will be called once this is out of scope
// Postcondition: All data will be deallocated and removed from memory. Can be
//		verified by running on Valgrind or checking memory leaks.
// Return: --
Graph::~Graph() {
	clearVertices();
}

// ----------------------------------- Operator= ------------------------------
// Description:	Will clear any existing data, copy items from parameter src,
//		and return pointer to this. 
// Precondition: Takes an existing Graph with size < MAX_VERTICES as parameter
//		This will contain same values as src for all members, but will contain 
//		different addresses, as it is a deep copy.	
// Return: Returns this.
Graph& Graph::operator=(const Graph& src) {
	clearVertices();
	this->copyItems(src);
	return *this;
}

// ----------------------------------- copyItems ------------------------------
// Description: Will copy all contents in VertexNode array and Table 2d array,
//		through deep copy as well as size. 
// Precondition: Will assume the Graph is empty and src size is < MAX_VERTICES
//		This will only be called by the copy constructor and operator=.
// Postcondition: Created new allocated data and copied all contents of Graph
// Return: --
void Graph::copyItems(const Graph& src){

	size = src.size;

	//copy VertexNode[];
	for (int i = 0; i <= size; i++) {

		// copy data
		if (src.vertices[i].data != NULL) {
			// create new Vertex and set string data
			Vertex* nData = new Vertex;
			std::string strData = src.vertices[i].data->getData();
			nData->setData(strData);

			vertices[i].data = nData;
		}
		
		// Copy edgeNode list
		if (src.vertices[i].edgeHead != nullptr) {
			// create new node and set values for head by copying src head
			EdgeNode* currPtr = new EdgeNode;
			currPtr->adjVertex = src.vertices[i].edgeHead->adjVertex;
			currPtr->weight = src.vertices[i].edgeHead->weight;
			vertices[i].edgeHead = currPtr;

			// get next src edgeNode before going into while loop
			EdgeNode* srcPtr = src.vertices[i].edgeHead->nextEdge;

			// copy rest of linked list
			while (srcPtr != nullptr) {
				// create new node and set values
				EdgeNode* edgeNodeIn = new EdgeNode;
				edgeNodeIn->adjVertex = srcPtr->adjVertex;
				edgeNodeIn->weight = srcPtr->weight;

				// next EdgeNode in linkedlist will be new node
				currPtr->nextEdge = edgeNodeIn;

				currPtr = currPtr->nextEdge;
				srcPtr = srcPtr->nextEdge;
			}
		}
	}

	// Copy Table[][] contents
	for (int row = 0; row <= size; row++) {
		for (int col = 0; col <= size; col++) {
			// copy each value
			T[row][col].path = src.T[row][col].path;
			T[row][col].dist = src.T[row][col].dist;
			T[row][col].vertexID = src.T[row][col].vertexID;
			T[row][col].visited = src.T[row][col].visited;

		}
	}
}

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
void Graph::clearVertices() {
	// Clear Table[][]
	clearTableArray();

	// clear data and edgeNode list for each cell in vertices that contain data
	for (int i = 0; i <= size; i++) {
		if (vertices[i].data) {
			delete vertices[i].data;
			vertices[i].data = NULL;
		}

		if (vertices[i].edgeHead) {
			EdgeNode* currPtr = vertices[i].edgeHead;
			// traverse through linked list and delete EdgeNodes
			while (currPtr != nullptr) {
				EdgeNode* nextPtr = currPtr->nextEdge;
				delete currPtr;
				currPtr = nextPtr;
			}

			vertices[i].edgeHead = nullptr;
		}
	}

	// reset size to 0
	size = 0;
}


void Graph::clearTableArray() {

	// for cells in T that contain data, replace it with intialized data
	for (int row = 0; row <= size; row++) {
		for (int col = 0; col <= size; col++) {
			// copy each value
			T[row][col].path = 0;
			T[row][col].dist = INT_MAX;
			T[row][col].vertexID = 0;
			T[row][col].visited = false;
		}
	}
}


//-------------------------------- buildGraph ---------------------------------
// Builds a graph by reading data from an ifstream
// Preconditions:  infile has been successfully opened and the file contains
//                 properly formated data (according to the program specs)
// Postconditions: One graph is read from infile and stored in the object
// Return: --
void Graph::buildGraph(std::ifstream& infile) {

	infile >> size;                          // data member stores array size
	if (infile.eof())
		return;
	infile.ignore();                         // throw away '\n' to go to next line

	// get descriptions of vertices
	for (int v = 1; v <= size; v++) {
		std::string name;
		std::getline(infile, name);

		// create and define data of Vertex
		Vertex* vPtr = new Vertex();
		vPtr->setData(name);

		// set data to vertex
		vertices[v].data = vPtr;

	}

	// fill cost edge array
	int src = 1, dest = 1, weight = 1;
	for (;;) {
		infile >> src >> dest >> weight;
		if (src == 0 || infile.eof())
			break;
		insertEdge(src, dest, weight);
	}
}

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
void Graph::insertEdge(const int& src, const int& dest, const int& weight) {

	EdgeNode* newENode = new EdgeNode;
	newENode->adjVertex = dest;
	newENode->weight = weight;

	// get pointer to edgeHead of src
	EdgeNode* front = this->vertices[src].edgeHead;	

	if (front == nullptr) {
		// if edgehead is empty, add first edge
		newENode->nextEdge = this->vertices[src].edgeHead;
		this->vertices[src].edgeHead = newENode;						

	} else {
		EdgeNode* currPtr = front;
		bool inserted = false;

		// if head has the same adjacent vertex w/ different weight, replace it.
		if (currPtr->adjVertex == dest && currPtr->weight != weight) {
			currPtr->weight = weight;
			inserted = true;
			delete newENode;

		} else {
			// iterate through list until nextEdge is nullptr
			while (currPtr->nextEdge != nullptr) {
				currPtr = currPtr->nextEdge;
				// If edgeNode w/ same src and distance exists in middle of LinkedList
				if (currPtr->adjVertex == dest && currPtr->weight != weight) {
					currPtr->weight = weight;
					inserted = true;
					delete newENode;
					break;
				}
			}
		}

		if (inserted == false) {
			currPtr->nextEdge = newENode;			// add edge to end of list
		}
	}
}

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
void Graph::findShortestPath() {

	for (int src = 1; src <= size; src++) {

		// intialize min priority queue
		std::priority_queue<pair<int, int>, std::vector<pair<int, int>>, 
			std::greater<pair<int, int>>> queue;

		//set DsourceVertex = 0
		T[src][src].vertexID = src;
		T[src][src].dist = 0;
		
		/*	by default, min heap is ordered by first element in pair
			so, we are putting distance as first element	*/
		queue.push(make_pair(T[src][src].dist, src));

		int count = size;
		while (count > 0 && !queue.empty()) {
			// let v be the unvistied vertex with minimum
			int vNum = queue.top().second;
			T[src][vNum].vertexID = vNum;
			queue.pop();
			
			// will be marked visIted once removed from queue
			T[src][vNum].visited = true;

			// pointer to src's VertexNode's EdgeHead 
			EdgeNode* currEdge = this->vertices[vNum].edgeHead;

			// for each vertex w adjacent to v
			while (currEdge != nullptr) {
				int wNum = currEdge->adjVertex;
				T[src][wNum].vertexID = wNum;

				// If Dw > Dv + dv,w
				if (T[src][wNum].dist > T[src][vNum].dist + currEdge->weight) {

					// set Dw = Dv + dv,w
					T[src][wNum].dist = T[src][vNum].dist + currEdge->weight;

					// remember that the best path to w goes through v
					T[src][wNum].path = vNum;

					// push w to queue
					queue.push(make_pair(T[src][wNum].dist, wNum));
				}
				// traverse through EdgeNode linkedlist
				currEdge = currEdge->nextEdge;
			}
			count--;
		}
	}
}

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
void Graph::displayAll() {

	// Create column titles
	cout << "Description" << setw(20);
	cout << "From" << setw(10);
	cout << "To" << setw(10);
	cout << "Dist" << setw(20);
	cout << "Path" << setw(10);
	cout << endl;

	for (int src = 1; src <= size; src++) {
		// print src string data
		cout << vertices[src].data->getData() << endl;

		// for every src and destination, print shortest distance & path
		for (int dest = 1; dest <= size; dest++) {

			// print only if destination is not src
			if (src != dest) {
				cout << setw(30);
				std::string path = "";
				printRow(src, dest, path);
			}

		}
	}
}

// ------------------------------------ display -------------------------------
// Description: This will display the shortest distance and path from source
//		and destination. It will also print out the locations you are visiting
//		in the shortest path. Because, this contains printRow that takes a 
//		string address by parameter, it cannot be set to const.
// Precondition: -- 
// Postcondition: Will print src, dest, shortest path, shortest distance, and
//		path locations onto cout. If it doesn't exist, path will be represent
//		"--" and there will be no path locations.
// Return: --
void Graph::display(const int& src, const int& dest) {

	// print src, destination, and path. generate & capture path
	std::string path = "";
	printRow(src, dest, path);

	// print path locations using string path generated
	stringstream pathReader(path);
	while (1) {
		int vertex;
		pathReader >> vertex;
		if (!pathReader)
			break;

		// for every vertices, print the string data location
		cout << vertices[vertex].data->getData() << endl;
	}
}

// ----------------------------------- printRow -------------------------------
// Description: This will print the source, destination, shortest distance, 
//		and corresponding path in one line. 
// Precondition: It assumes that source and distance is not equal and that
//		path is an empty string. 
// Postcondition: Src, dest, shortest distance, and path will be printed 
//		to cout. If source is the destination, it will not print anything.
//		If there is no path, it will print -- for distance.
// Return: --
void Graph::printRow(const int& src, int dest, std::string& path) {

	// will only print if dest is not equal to src
	if (src != dest) {
		// prints src
		cout << src << setw(10);

		// prints dest
		cout << dest << setw(10);

		// only print distance if src has a way to dest
		if (T[src][dest].dist != INT_MAX) {
			cout << T[src][dest].dist << setw(20);
		} else {
			cout << "--" << setw(20);
		}

		// generate and print path
		tracePath(src, dest, path);
		cout << path << endl;
	}
}


// ---------------------------------- tracePath -------------------------------
// Description: Recursive function that finds the shortest path by working
//		backwards from the destination to the source. 
// Precondition: It assumes that source and distance is not equal and that
//		path is an empty string. 
// Postcondition: Returns the path by updating the path parameter. 
//		If there is no path, path will be an empty string.
// Return: --
void Graph::tracePath(const int& src, int& dest, std::string& path) {

	// retrieve Table pointer from T
	Table* tablePtr = &T[src][dest];
	
	// handle exception of no path
	if (tablePtr->dist == INT_MAX) {
		return;
	}

	// base case 
	if (tablePtr->dist == 0) {
		path += std::to_string(tablePtr->vertexID);
		return;
	}

	// recursive call
	tracePath(src, tablePtr->path, path);

	// add path of Table pointer to existing string
	path += " " + std::to_string(tablePtr->vertexID);

}

// --------------------------------- removeEdge --------------------------------
// Description: This will locate src VertexNode by using parameter src as index.
//		It ill take that VertexNode's edgehead and traverse through it until
//		it reaches the node with the same adjacentVertex and remove it. It will
//		deallocate any data that was dynamically allocated. 
// Precondition: An edge between src and destination should exist.
// Postcondition: Removes the edge from Vertices and also updates shortest paths
// Return: --
void Graph::removeEdge(const int& src, const int& dest) {

	// if linkedlist is empty, return 
	if (vertices[src].edgeHead == nullptr) {
		return;
	}

	EdgeNode* currPtr = vertices[src].edgeHead;

	// if edgeHead is equal to what's to be removed
	if (currPtr->adjVertex == dest) {
		
		// set new head
		vertices[src].edgeHead = currPtr->nextEdge;

		// delete currPtr containing first item on edgeNode
		delete currPtr;
		return;
	}
	
	EdgeNode* prevPtr = currPtr;

	/*  iterate through list until currPtr adjVertex is dest
		or we are at the end of the list */
	while (currPtr->adjVertex != dest && currPtr != nullptr) {
		prevPtr = currPtr;
		currPtr = currPtr->nextEdge;
	}

	if (currPtr == nullptr) {
		/* if the node to be removed is at the end, set end 
		to nullptr by setting prevPtr to nullptr */
		prevPtr->nextEdge = nullptr;

	} else {
		// skip over edgeNode that needs to be removed
		prevPtr->nextEdge = currPtr->nextEdge;
	}

	delete currPtr;			// deletes node 

	// clears and updates Table[][]
	clearTableArray();
	findShortestPath();
}



