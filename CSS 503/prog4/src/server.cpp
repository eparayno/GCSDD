/* SERVER.CPP
 * Date: 06/05/2020
 * Author: Professor Dimpsey
 * Edited by: Erika Parayno (SID#: 1425156)
 * Description: 
 * Assumptions:  -  We know the port that the client will be trying to connect to
 *               -  Client has given appropriate arguments
 */
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iostream>
#include <thread>

using namespace std;

const int BUFFSIZE = 1500;
const int NUM_CONNECTIONS = 5;

// Description: Parameter holder class
// Pre-condition: None
// Post-condtion: Have intialize serverSD and databuf
class ThreadParam {
public:
	 ThreadParam() {}
	 int serverSD;
	 char * databuf;
};

void * threadRunner (void *);

// Description: Connects to a socket and creates new threads for each client request that needs to be served.
// Pre-condition: Accepts only one argument, which is port number
// Post-condtion: Will continue to accept any client until killed
int main(int argc, char *argv[])
{
	// STEP 1: Allocate dataBuf[BUFSIZE], where BUFSIZE = 1500 to read in data being sent by client
	char databuf[BUFFSIZE];
	bzero(databuf, BUFFSIZE);

	// build address
	int port = atoi(argv[1]);
	sockaddr_in acceptSocketAddress;
	bzero((char *)&acceptSocketAddress, sizeof(acceptSocketAddress));
	acceptSocketAddress.sin_family = AF_INET;
	acceptSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	acceptSocketAddress.sin_port = htons(port);

	// open socket
	int serverSD = socket(AF_INET, SOCK_STREAM, 0);
	const int on = 1;
	setsockopt(serverSD, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(int));
	cout << "Socket #: " << serverSD << endl;

	// bind to socket
	int rc = bind(serverSD, (sockaddr *)&acceptSocketAddress, sizeof(acceptSocketAddress));
	if (rc < 0)
	{
		cerr << "Bind Failed" << endl;
	}

	// the use the listen() system call to tell the server how many concurrent connections to listen for
	listen(serverSD, NUM_CONNECTIONS);       //setting number of pending connections

	// Dispatch loop
	while (true) {
 
		// create new socket
		sockaddr_in newSockAddr;
		socklen_t newSockAddrSize = sizeof(newSockAddr);
		int newSD = accept(serverSD, (sockaddr *) &newSockAddr, &newSockAddrSize);
		cout << "Accepted Socket #: " << newSD <<endl;

		// create new data buffer
		char newDatabuff[BUFFSIZE];
    memset(newDatabuff, '\0', sizeof(newDatabuff[0]) * BUFFSIZE);

		// create param to pass to thread creation
		ThreadParam * param = new ThreadParam();
		param->databuf = newDatabuff;
		param->serverSD = newSD;

		// create thread
    pthread_t serviceThread;
		pthread_create( &serviceThread, NULL, threadRunner, (void *)param ); // edit

    // separate thread of execution from thread object
    pthread_detach(pthread_self());
	}
 
	close(serverSD);
	return 0;
}

// Description: Will create a new thread for the new socket socket connection
// Pre-condition: Needs to have associated threadparam intialized
// Post-condtion: Will have read appropriate size of data and send number of readcalls attempted to client
void *threadRunner (void * arg) {
	ThreadParam param = *(ThreadParam *) arg;
	//accept new connection
	// STEP 2: Recieve a message from client with number of iterations to perform
  int repetition;
	read(param.serverSD, &repetition, sizeof(repetition));

	// STEP 3: Read from the client the appropriate number of iterations of BUFSIZE amounts of data
   int readCalls = 0;
   int readThisRep;
   for (int set = 0; set < repetition; set++) {
     readThisRep = 0;
     while (readThisRep < BUFFSIZE) {
       int bytesRead = read(param.serverSD, param.databuf, BUFFSIZE - readThisRep);
       readThisRep += bytesRead;
       readCalls++;
     }
   } 

	// STEP 4: Send the number of read() calls made as an acknowledgment to the client
	write(param.serverSD, &readCalls, sizeof(readCalls));

	// STEP 5: Close this connection.
	close(param.serverSD);
 
	// STEP 6: Terminate the thread
	pthread_exit(NULL);
}




