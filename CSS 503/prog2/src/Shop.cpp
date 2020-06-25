// SHOP.CPP
// Author: Professor Dimpsey
// Edited by: Erika Parayno (SID #1425156)
// Date: May 12, 2020
// Description: Creates the shop that defines the behavior of barbers and clients. Uses multithreading to ensure transactions are made free of deadlock / race conditions.

#include <iostream> // cout
#include <sstream>  // stringstream
#include <string>   // string
#include "Shop.h"

// Description: Constructor helper
// Pre-condition: Called by constructors
// Post-condition: intializes all variables necessary for store to operate
void Shop::init( ) {
	// initialize lock
	pthread_mutex_init( &mutex, NULL );

	// initialize conditions
	pthread_cond_init(&cond_customers_waiting, NULL);
	cond_customer_served = new pthread_cond_t[totalBarbers];
	cond_barber_paid = new pthread_cond_t[totalBarbers];
	cond_barber_sleeping = new pthread_cond_t[totalBarbers];

	in_service = new bool[totalBarbers];
	service_chair = new int[totalBarbers];
	money_paid = new bool[totalBarbers];

	for (int i = 0; i < totalBarbers; i++ ) {
		service_chair[i] = 0;
		in_service[i] = false;
		pthread_cond_init(&cond_customer_served[i], NULL);
		pthread_cond_init(&cond_barber_paid[i], NULL);
		pthread_cond_init(&cond_barber_sleeping[i], NULL);
	}
}

// Description: prints an int
// Pre-condition: Takes in an int
// Post-condition: Returns an string version of int parameter
string Shop::int2string(int i ) {
	stringstream out;
	out << i;
	return out.str( );
}

// Description: prints lines of output
// Pre-condition: Takes an int and message
// Post-condition: Prints formatted sentence on cout
void Shop::print(int person, string message ) {
	cout << ( ( person > 0 ) ? "customer[" : "barber  [" );
	if ( person < 0) {
		person = person * -1; // to print a positive barber
	}
	cout << person << "]: " << message << endl;
}

// Description: Return barber ID or -1 (not served)
// Pre-condition: Is called by customer thread (identified by int id) to visit the shop.
// Post-condition: Returns barberID if matched successfully, -1 if not
int Shop::visitShop( int customerId ) {
   // lock before entering the critical section
	pthread_mutex_lock( &mutex );
	int myBarberId;

	if (waiting_chairs.size( ) == max && barberAvail() == 0) { // waiting chairs are all occupied, checks all service chairs
		print(customerId, "leaves the shop because of no available waiting chairs.");
		++nDropsOff;
		pthread_mutex_unlock( &mutex );
		return -1;                 // leave the shop
	}

	if (barberAvail() == 0) {   // if all the barbers are busy
		// someone is being served or transiting from a waiting to a service chair, take a waiting chair
		waiting_chairs.push(customerId);
		print(customerId, "takes a waiting chair. # waiting seats available = "
								+ int2string(max - waiting_chairs.size()));
		// wait for barber to wake me up
		pthread_cond_wait(&cond_customers_waiting, &mutex);
		// pop me out of the queue
		waiting_chairs.pop();
	}

	// get my barber whose id is barberId
	myBarberId = getBarber();
	//sit in customer chair
	service_chair[myBarberId] = customerId;
	print(customerId, "moves to the service chair[" + int2string(myBarberId) + "] # waiting seats available = "
							+ int2string(max - waiting_chairs.size()));

	// Have barberId start my haircut
	in_service[myBarberId] = true;
	// wake up the barber just in case if he is sleeping
	pthread_cond_broadcast(&cond_barber_sleeping[myBarberId]);
	// leave the critical section
	pthread_mutex_unlock( &mutex ); // unlock
	// return barberID
	return myBarberId;
}

// Description: Will finalize customer interaction in shop
// Pre-condition: Is called by customer thread to visit the shop
// Post-condition: Will have paid the barber and leave shop
void Shop::leaveShop(int customerId, int barberId ) {
	// lock before entering critical section
	pthread_mutex_lock( &mutex );
	print( customerId, "wait for barber[" + int2string(barberId) + "] to be done with hair-cut" );

	while (in_service[barberId]) {                  // while barber ID is cutting my hair
		pthread_cond_wait( &cond_customer_served[barberId], &mutex );  // just sit.
	}

	// pay barber
	money_paid[barberId] = true;
	// signal paid barber
	pthread_cond_broadcast( &cond_barber_paid[barberId] );
	print( customerId, "says good-bye to the barber." );
	// finish transaction & leave critical section
	pthread_mutex_unlock( &mutex ); // unlock
}

// Description: Will check if there is a customer to determine work or sleep
// Pre-condition: Is called by barber thread
// Post-condition: WIll sleep if chairs are empty and not servicing, otherwise do work.
void Shop::helloCustomer( int barberId ) {
	// lock before entering the critical section
	pthread_mutex_lock( &mutex );
	int myCustomer;

	// if all waiting chairs are empty and not servicing,
	if (waiting_chairs.empty() && service_chair[barberId] == 0) {
		print( -barberId, "sleeps because of no customers." );
		in_service[barberId] = false;
		service_chair[barberId] = 0 - barberId;
		while (!in_service[barberId]) {
			pthread_cond_wait(&cond_barber_sleeping[barberId], &mutex); // then, let's sleep
		}
	}

	// if there there is someone on waiting chair and not servicing
	if (service_chair[barberId] == 0) {
		while (!in_service[barberId]) {
			pthread_cond_wait(&cond_barber_sleeping[barberId], &mutex);
		}

		print( -barberId,
				 "starts a hair-cut service for customer[" + int2string( service_chair[barberId] ) +"].");
	}

	// unlock after leaving critical section
	pthread_mutex_unlock( &mutex );  // unlock
}

// Description: Barber will wait until he or she is paid and move on to next customer
// Pre-condition: Is called by a barber thread
// Post-condition: Must have signaled next customer waiting
void Shop::byeCustomer( int barberId ) {
	// Lock before entering critical section
	pthread_mutex_lock( &mutex );
	print( -barberId, "says he's done with a hair-cut service for customer[" +
							int2string( service_chair[barberId] ) +"]");

	// update arrays
	in_service[barberId] = false;
	money_paid[barberId] = false;

	// wakes up my customer
	pthread_cond_broadcast( &cond_customer_served[barberId] ); // CHANGES HERE
	// wait for customer to pay before I take a new one
	while (!money_paid[barberId]) {
		pthread_cond_wait(&cond_barber_paid[barberId], &mutex);
	}
	service_chair[barberId] = 0;
	print( -barberId, "calls in another customer" );
	// wakes up another customer who is waiting on a waiting chair
	pthread_cond_signal(&cond_customers_waiting);

	// leave critical section
	pthread_mutex_unlock( &mutex );  // unlock
}

Shop::~Shop() {
   pthread_cond_destroy(cond_customer_served);
   free(cond_customer_served);
   pthread_cond_destroy(cond_barber_paid);
   free(cond_barber_paid);
   pthread_cond_destroy(cond_barber_sleeping);
   free(cond_barber_sleeping);

   in_service = NULL;
   delete[] in_service;
   service_chair = NULL;
   delete[] service_chair;
   money_paid = NULL;
   delete[] money_paid;
}

// Description: Returns number of free barbers
// Pre-condition: None
// Post-condition: Returns number
int Shop::barberAvail() {
	int avail = 0;
	for (int i = 0; i < totalBarbers; i++) {
		if (service_chair[i] <= 0 ) {
			avail++;
		}
	}
	return avail;
}

// Description: Picks next free barber
// Pre-condition: None
// Post-condition: returns barberID who is not servicing a customer. If all busy, return -1.
int Shop::getBarber() {
	int myBarber = -1;
	for (int i = 0; i < totalBarbers; i++) {
		if (service_chair[i] <= 0) {   // barber is sleeping
			myBarber = i;     // keep index of the barber
			break;
		}
	}
	return myBarber;
}



