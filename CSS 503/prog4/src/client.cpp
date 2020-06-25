/* CLIENT.CPP
 * Date: 06/01/2020
 * Author: Professor Dimpsey
 * Edited by: Erika Parayno (SID#: 1425156)
 * Description: client program to demonstrate sockets usage 
 * Assumptions:   - Server code is being run by server computer
                  - We know port that the server is connected to 
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
#include <chrono>   

using namespace std;
using namespace chrono;

const int BUFFSIZE=1500;

// Description: Connects with the server and measures different write system calls performance
// Precondition: Takes all valid arguments, and server code is up and running. 
// Postcondition: Prints output via cout prior to closing client
int main(int argc, char *argv[])
{
    // argument size validation
    if (argc != 7)
    {
       cerr << "Usage: " << argv[0] << "serverName" << endl;
       return -1;
    }

    //1st argument: servername = the name of the server
    char * serverName = argv[1];
    
    // 2nd argument: port = the IP prot number used by server (last 5 digits of student id)
    char * serverPort = argv[2];
    
    // 3rd argument: repetition = the repetition of sending a set of data buffers
    int repetition = atoi(argv[3]);
    if (repetition < 0) {
      cout << "Error: Negative numbers not allowed" << endl;
      return -1;
    }
    
    // 4th argument: the number of data buffers
    int nbufs = atoi(argv[4]);
    if (nbufs < 1) {
      cout << "Error: Please enter a positive number" << endl;
      return -1;
    }
    
    // 5th argument: the size of each data buffer (in bytes)
    int bufsize = atoi(argv[5]);
    if (bufsize < 1) {
      cout << "Error: Please enter a positive number" << endl;
      return -1;
    }
    
    // 6th argument: type = the type of transer scenario: 1, 2, or 3
    int type = atoi(argv[6]);
    if (type < 1 || type > 3) {
      cout << "Error: Please enter a type integer between 1, 2, or 3" << endl;
      return -1;
    }
    
    // intialize addrinfo variables
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int clientSD = -1;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;					      /* Allow IPv4 or IPv6*/
    hints.ai_socktype = SOCK_STREAM;					/* TCP */
    hints.ai_flags = 0;							         /* Optional Options*/
    hints.ai_protocol = 0;						         /* Allow any protocol*/
   
    // STEP 1: Establish a connection to a server
    /* Use getaddrinfo() to get addrinfo structure corresponding to serverName / Port
       This addrinfo structure has internet address which can be used to create a socket too*/
    int rc = getaddrinfo(serverName, serverPort, &hints, &result);
    if (rc != 0) {
       cerr << "ERROR: " << gai_strerror(rc) << endl;
       exit(EXIT_FAILURE);
    }

    // Iterate through addresses and connect
    for (rp = result; rp != NULL; rp = rp->ai_next) {
    
        // attempt to create endpoint of communication and store return (FD) clientSD
        clientSD = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (clientSD == -1) {
            continue;
        }
        
		    // A socket has been successfully created, attempt to connect
        rc = connect(clientSD, rp->ai_addr, rp->ai_addrlen);
        if (rc < 0) {
            cerr << "Connection Failed" << endl;
            close(clientSD);
            return -1;
        } else {
            // break from while loop
            break;
        }
    }

    // if no valid address was returned after iterating thru if loop, exit
    if (rp == NULL) {
        cerr << "No valid address" << endl;
        exit(EXIT_FAILURE);
    } 
    // if valid address was found, print clientSD
    else {
        //cout << "Client Socket: " << clientSD << endl;
    }
    
    // free address data from memory
    freeaddrinfo(result);

    /* STEP 2: Send a message to the server letting it know the number of iterations 
     * of tests it will perform*/
    write(clientSD, &repetition, sizeof(repetition));
        
    // create data buffer and make null
    char databuf[nbufs][bufsize];
    memset(databuf, '\0', sizeof(databuf[0][0]) * nbufs * bufsize);

    // initialize chrono variables and start timers before the tests
    time_point<chrono::steady_clock> start, end;
    start = chrono::steady_clock::now();
    
    // STEP 3: Perform the appropriate number of tests with the server
    // measure the time this takes, using chrono time library
    for (int iteration = 0; iteration < repetition; iteration++) {
       /* Multiple writes: invokes the write() system call for each data buffer, thus 
          resulting in calling as many write()s as the number of data buffers, (i.e., nbufs) */
       if (type == 1) {
          for (int j = 0; j < nbufs; j++) {
               write(clientSD, databuf[j], bufsize);
          }
       }
       
       /* writev: allocates an array of iovec data structures, each having its *iov_base field 
          point to a different data buffer as well as storing the buffer size in its iov_len field; 
          and thereafter calls writev() to send all data buffers at once. */
       if (type == 2) {
            struct iovec vector[nbufs];
            for (int j = 0; j < nbufs; j++) {
               vector[j].iov_base = databuf[j];
               vector[j].iov_len = bufsize;
            }
            writev(clientSD, vector, nbufs);
       }
       
       /* single write: allocates an nbufs-sized array of data buffers, and thereafter calls write() 
          to send this array, (i.e., all data buffers) at once.*/
       if (type == 3) {
         write(clientSD, databuf, nbufs * bufsize);
       }
    }

    // end chrono time
    end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start; 
    
    // STEP 4: Recieve from the server a message
    int numberOfReads;
    read(clientSD, &numberOfReads, sizeof(numberOfReads));
    
    // STEP 5: Print information about the test, using chrono library
  	cout << "[Test: type = " << type << ", nbufs = " << nbufs << ", bufsize = " << bufsize << "]: ";
  	cout << "time = " << elapsed_seconds.count()*1000000 << " usec, ";
  	cout << "#reads = " << numberOfReads << ", ";
  	cout << "throughput = " << ((bufsize * repetition * 8 * nbufs) * 0.000000001) / elapsed_seconds.count() << " Gbps" << endl;; // FINISH
	
    //sleep(100);    
    
    // STEP 6: Close the socket
    close(clientSD);
    return 0;
}



