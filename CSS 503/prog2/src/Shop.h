#ifndef _SHOP_H_
#define _SHOP_H_

#include <pthread.h>
#include <queue>
#include <string>

using namespace std;

#define DEFAULT_CHAIRS 3 	// the default number of chairs waiting = 3

#define DEFAULT_BARBERS 1  // default nubmer of barbers = 1

class Shop {
public:

	 // Description: Constructor that initializes a Shop object with nBarbers and nChairs
	 // Pre-condition: Called in driver.cpp
	 // Post-condition: Initializes shop and calls init to intialize all other values
	 Shop(int nBarbers, int nChairs ) : totalBarbers(nBarbers), totalChairs(nChairs),
													nDropsOff(0), max(nChairs)
	 { init( ); };

	 // Description: Default constructor that initializes a Shop object with 1 barber and 3 chairs
	 // Pre-condition: Called in driver.cpp
	 // Post-condition: Initializes shop and calls init to intialize all other values
	 Shop( ) : totalBarbers(DEFAULT_BARBERS), totalChairs(DEFAULT_CHAIRS),
				  nDropsOff(0), max(DEFAULT_CHAIRS)
	 { init( ); };

	 // Description: Return barber ID or -1 (not served)
	 // Pre-condition: Is called by customer thread (identified by int id) to visit the shop.
	 // Post-condition: Returns barberID if matched successfully, -1 if not
	 int visitShop( int customerId );

	 // Description: Will finalize customer interaction in shop
	 // Pre-condition: Is called by customer thread to visit the shop
	 // Post-condition: Will have paid the barber and leave shop
	 void leaveShop( int customerId, int barberId );

	 // Description: Will check if there is a customer to determine work or sleep
	 // Pre-condition: Is called by barber thread
	 // Post-condition: WIll sleep if chairs are empty and not servicing, otherwise do work.
	 void helloCustomer( int id );

	 // Description: Barber will wait until he or she is paid and move on to next customer
	 // Pre-condition: Is called by a barber thread
	 // Post-condition: Must have signaled next customer waiting
	 void byeCustomer( int id );

	 // Description: Destructor
	 // Pre-condition: Is called when shop is out of scope
	 // Post-condition: Deallocates any new object made in the class
	 ~Shop();

	 int nDropsOff;              // the number of customers dropped off

private:
	 pthread_mutex_t mutex;
	 pthread_cond_t cond_customers_waiting;
	 pthread_cond_t *cond_customer_served;
	 pthread_cond_t *cond_barber_paid;
	 pthread_cond_t *cond_barber_sleeping;

	 queue<int> waiting_chairs;  // includes the ids of all waiting threads

	 // Description: Constructor helper
	 // Pre-condition: Called by constructors
	 // Post-condition: intializes all variables necessary for store to operate
	 void init( );

	 // Description: prints an int
	 // Pre-condition: Takes in an int
	 // Post-condition: Returns an string version of int parameter
	 string int2string( int i );

	 // Description: prints lines of output
	 // Pre-condition: Takes an int and message
	 // Post-condition: Prints formatted sentence on cout
	 void print( int person, string message );

	 int max;              // the max number of threads that can wait

	 int* service_chair;          // indicate the current customer thread id
	 bool* in_service;				// indicate current status of barber
	 bool* money_paid;				// indicate whether barber has been paid

	 int totalBarbers;
	 int totalChairs;

	 // Description: Returns number of free barbers
	 // Pre-condition: None
	 // Post-condition: Returns number
	 int barberAvail();

	 // Description: Picks next free barber
	 // Pre-condition: None
	 // Post-condition: returns barberID who is not servicing a customer. If all busy, return -1.
	 int getBarber();

};


#endif
