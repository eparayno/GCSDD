/* LAB2.CPP
 Author: Professor Dimpsey
 Edited by: Erika Parayno (SID#: 1425156) & Melinda Johnson (SID#: 1978413)
 Date: 04/28/20
 Description: This lab intends to familiarize with pthread synchronization. This program
 suspends and resumes one thread after another. */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int nThreads;            // #threads

int turn;                // turn points which thread should run
pthread_mutex_t mutex1;   // a lock for this critical section
pthread_cond_t *cond;    // array of condition variable[nThreads]


/* Description: This method suspends and resumes one thread after another using
 mutex locks. Before moving on to next turn, all threads will
 have ran the current turn.
 Pre-condition: thread identifier accepted as arg
 Post Condition: Each thread must have gone through the loop (10 times), and
 printed on cout.*/
void *thread_func(void *arg)
{
   int id = ((int *)arg)[0];                  // this thread's identifier
   delete (int *)arg;
   
   for (int loop = 0; loop < 10; loop++) // Run 10 times
   {
         // enter the critical section
      pthread_mutex_lock(&mutex1);
      
      while (turn != id)
      {
            // wait until the (id - 1)th thread signals me.
         pthread_cond_wait(&cond[id], &mutex1);
         
      }
      
      cout << "thread["<< id << "] got " << loop << "th turn" << endl;
      
      /* identify next thread to be signaled and save it to global variable.
       You want to signal id + 1, unless you reach nthreads, then you have to
       start back at 0 */
      if (turn < nThreads - 1)
      {
         turn = turn + 1;
      }
      else
      {
         turn = 0;
      }
      
         // signal the next thread
      pthread_cond_signal(&cond[turn]);
      
         // leave the critical section
      pthread_mutex_unlock(&mutex1);
      
   }
   
   return 0;
}

/* Description: Will print error message if invalid args. Otherwise, it will proceed to
 run program based with arguments as number of threads.
 Pre-condition: Accepts int argument
 Post Condition: Created nThreads, run each thread after the other, and joins. */
int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cerr << "usage: lab2 #threads" << endl;
      return -1;
   }
   
   nThreads = atoi( argv[1] );
   if (nThreads < 1)
   {
      cerr << "usage: lab1 #threads" << endl;
      cerr << "where #threads >= 1" << endl;
      return -1;
   }
   
   pthread_t *tid = new pthread_t[nThreads];  // an array of thread identifiers
   cond = new pthread_cond_t[nThreads];       // an array of condition variables
   turn = 0;                                  // points to which thread should run
   
   for (int i = 0; i < nThreads; i++)
   {
      int *id = new int[1];
      id[0] = i;
      pthread_create( &tid[i], NULL, thread_func, (void *)id );
   }
   
   for (int i = 0; i < nThreads; i++) // wait for all threads
   {
      pthread_join( tid[i], NULL );
   }
   
   delete[] cond;
   
   delete[] tid;
   
}
