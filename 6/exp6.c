#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/types.h>

void *func(int n);
pthread_t philosopher[5];
pthread_mutex_t chopstick[5];

void main()
{

   long int i;
  for(i=1;i<=5;i++)
  pthread_mutex_init(&chopstick[i],NULL);
  
  for(i=1;i<=5;i++)
  pthread_create(&philosopher[i],NULL,(void *)func,(long int *) i);
  
  for(i=1;i<=5;i++)
  pthread_mutex_destroy(&chopstick[i]);
 }

void *func(int n)
{
  
  printf("\nPhilosopher %d is thinking",n);
  pthread_mutex_lock(&chopstick[n]);
  pthread_mutex_lock(&chopstick[(n+1)%5]);
  printf("\nPhilosopher %d is eating",n);
  //sleep(3);
  pthread_mutex_unlock(&chopstick[(n+1)%5]);
  pthread_mutex_unlock(&chopstick[n]);
  printf("\nPhilosopher %d has finished eating",n);
}
