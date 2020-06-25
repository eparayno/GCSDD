// DRIVER.CPP
// Author: Professor Dimpsey
// Edited by: Erika Parayno (SID #1425156)
// Date: May 12, 2020
// Description: Tests sleeping barbers problem. It creates the shop, the barbers and the clients.

#include <iostream>    // cout
#include <sys/time.h> // gettimeofday
#include <unistd.h>
#include "Shop.h"

using namespace std;

// THREADPARAM
// Description: Object which is used to pass more than one argument to the thread function.
class ThreadParam {
public:
	 ThreadParam (Shop *shop, int id, int serviceTime) :
				shop(shop), id(id), serviceTime(serviceTime) {};

	 Shop *shop; 	// a pointer to the Shop object
	 int id;
	 int serviceTime;
};

void *barber( void * );
void *customer( void * );

int main( int argc, char *argv[] ) {

	// 1. Receives the line arguments
	int nBarbers = atoi( argv[1] );
	int nChairs = atoi( argv[2] );
	int nCustomers = atoi( argv[3] );
	int serviceTime = atoi( argv[4] );

	pthread_t barber_thread[nBarbers];
	pthread_t customer_threads[nCustomers];

	// 2. Instantiates a shop which is an object from Shop class
	Shop shop(nBarbers, nChairs);

	// 3. Spawns the nBarbers number of barber threads. Each individual
	// gets passed as a pointer to the shop object (shared), the unique
	// identifier (0 ~ nBarbers - 1), and serviceTime
	for ( int i = 0; i < nBarbers; i++ ) {
		ThreadParam * param = new ThreadParam (&shop, i, serviceTime);
		pthread_create( &barber_thread[i], NULL, barber, (void *)param );
	}

	// 4. Loops spawning nCustomers, waiting a rando interval in u seconds
	// (i.e. usleep(rand() % 1000)) between each new customer being spawned.
	// All custoemr threads are passed in a pointer to the shop object and
	// the identifier (i.e. 1 ~nCustomers).
	for ( int i = 0; i < nCustomers; i++ ) {
		usleep( rand( ) % 1000 );
		int id = i + 1;
		ThreadParam * param = new ThreadParam (&shop, id, serviceTime);
		pthread_create( &customer_threads[i], NULL, customer, (void *)param );
	}

	// 5. Waits until all the customer threads are serviced and terminated
	for ( int i = 0; i < nCustomers; i++ ) {
		pthread_join( customer_threads[i], NULL );
	}

	// 6. Terminates all barber threads
	for (int i = 0; i < nBarbers; i++) {
		pthread_cancel(barber_thread[i]);
	}

	// print drop offs and end program
	cout << "# customers who didn't receive a service = " << shop.nDropsOff << endl;
	cout << "end of program" << endl;

	return 0;
}

// Description: Barber thread function
// Pre-condition: Created in main
// Post-condition: Creates a new barber thread
void *barber( void *arg ) {
	// extract parameters
	ThreadParam &param = *(ThreadParam *) arg;
	Shop &shop = *(param.shop);
	int id = param.id;
	int serviceTime = param.serviceTime;
	delete &param;

	// keep working until being terminated by main
	while( true ) {
		shop.helloCustomer( id );	// pick up a new customer
		usleep( serviceTime );
		shop.byeCustomer( id ); 	// release the customer
	}
	pthread_exit(NULL);
}

// Description: Customer thread function
// Pre-condition: Created in main
// Post-condition: Creates a new customer thread
void *customer( void *arg ) {
	// extract parameters
	ThreadParam &param = *(ThreadParam *) arg;
	Shop &shop = *(param.shop);
	int id = param.id;
	delete &param;

	// if assigned to barber i then wait for service to finish
	// -1 means did not get barber
	int barber = shop.visitShop(id);
	if (barber != -1) {
		shop.leaveShop(id, barber);	// wait until my service is finished
	}
	pthread_exit(NULL);
}


