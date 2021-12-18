//Munachimso Aneke
// Thread Synchronization

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "buffer.h"

// the buffer
buffer_item buffer[BUFFER_SIZE]; // buffer_item is an int
int index_no, in, out; // buffer index

// semaphore and mutex
sem_t empty, full;
pthread_mutex_t mutex;

int insert_item(buffer_item item);
int remove_item(buffer_item * item);
void initialization();
void *producer(void *param);
void *consumer(void *param);


int main( int argc, char *argv[4])
{
   // 1. Get command line arguments argv[1], argv[2], argv[3];
   if(argc != 4)
   {
      printf("Usage: %s sleep_time producer_threads consumer_threads\n", argv[0]);
      exit(1);
   }

   if (atoi(argv[2]) <= 0 || atoi(argv[3]) <= 0)
   {
      fprintf(stderr, "Number of producer and consumer threads must both be greater than  0\n");
      exit(1);
   }

   int sleep_time = atoi(argv[1]); // sleep time
   int pd_num = atoi(argv[2]); // num of producers threads
   int con_num = atoi(argv[3]); // num of consumer threads

   // 2. Initialize buffer
 
   initialization();
   
   // 3. Create Producer thread(s)
   pthread_t tid1[pd_num];
   /*pthread_attr_t attr1;
   pthread_attr_init(&attr1);*/

   for( int i = 0; i < pd_num; i++)
   {
      pthread_create(&tid1[i], NULL, producer, NULL);
   }

   //pthread_join(tid1, NULL);
   
   // 4. Create consumer thread(s)
    pthread_t tid2[con_num];
    /*pthread_attr_t attr2;  do I need 2 attribute since it's default
    pthread_attr_init(&attr2);*/

    for( int i = 0; i < pd_num; i++)
   {
      pthread_create(&tid2[i], NULL, consumer, NULL);
   }

    //pthread_join(tid2, NULL);
   // 5. Sleep
    sleep(sleep_time);
    
   // 6. Exit
   
   return 0;
}





int insert_item(buffer_item item)
{
   if(index_no < BUFFER_SIZE)
   {
      buffer[in] = item;
      in = (in + 1) % BUFFER_SIZE;
      index_no++;
      
      return 0;
   }
   else
   {
      //printf("insert failed!");
      return -1;
   }
   
}

int remove_item(buffer_item * item)
{
   if(index_no > 0)
   {
      * item = buffer[out];
      out = (out + 1) % BUFFER_SIZE;
      index_no--;

      return 0;
   }
   else
   {
      //printf("remove failed");
      return -1;
   }
}

void initialization()
{
   sem_init(&empty, 0, BUFFER_SIZE);
   sem_init(&full, 0, 0);
   pthread_mutex_init(&mutex, NULL);

   for(int i = 0; i < BUFFER_SIZE; i++) // initialise buffer elements
   {
      buffer[i] = 0;
   }

   index_no = 0; // initialise index
   in = 0;
   out = 0;
}

void *producer(void *param){
   buffer_item item;
   
   while(1)
   {
      sleep (rand()%10);  // 0 - 9 secs  
      item = rand() % 100; // 0-99

      sem_wait(&empty);
      pthread_mutex_lock(&mutex);
      if(insert_item(item))
      {
	 fprintf(stderr,"report error condition");
	 
      }
      else
      {
	 printf("producer %ld produced %d\n", pthread_self(), item);
      }
      pthread_mutex_unlock(&mutex);
      sem_post(&full);
   }
   
   //pthread_exit(0);
}

void *consumer(void *param){
   buffer_item item;
   
   while(1) {
      sleep(rand()%10); // 0-9 secs

      sem_wait(&full);
      pthread_mutex_lock(&mutex);
     
      if(remove_item(&item))
      {
	 fprintf(stderr, "report error condition");
	 
      }
      else
      {
	 printf("consumer %ld consumed %d\n", pthread_self(), item);
      }
      pthread_mutex_unlock(&mutex);
      sem_post(&empty);
   }
   
   //pthread_exit(0);
}
