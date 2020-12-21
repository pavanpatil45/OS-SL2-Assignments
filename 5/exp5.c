
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

void *writer_thr(int temp);
void *reader_thr(int temp);
sem_t mutex;
sem_t wrt;
int readcount=0,nwt,nrd;


void main()
{
  long int i;
  sem_init(&mutex,0,1);
  sem_init(&wrt,0,1);
  pthread_t reader[100],writer[100];
  printf("\n Enter number of readers:");
  scanf("%d",&nrd);
  printf("\n Enter number of writers:");
  scanf("%d",&nwt);
  
  for(i=1;i<=nwt;i++)
  {
    pthread_create(&writer[i],NULL,(void *)writer_thr,(int *)i);
    pthread_join(writer[i],NULL);
  }
  
  for(i=1;i<=nrd;i++)
  {
    pthread_create(&reader[i],NULL,(void *)reader_thr,(int *)i);
  }
  
   
  
  for(i=1;i<=nrd;i++)
  {
    pthread_join(reader[i],NULL);
  }
    
  sem_destroy(&wrt);
  sem_destroy(&mutex);

}



void *reader_thr(int temp)
{
  
  printf("\n Reader %d is trying to enter database for reading.",temp);
  sem_wait(&mutex);
  readcount++;
  if(readcount==1)
  sem_wait(&wrt);
   sem_post(&mutex);
 
  printf("\nReader %d is now reading in database.",temp);
  
 
  sem_wait(&mutex);
  readcount--;
  if(readcount==0)
  
  sem_post(&wrt);  
  sem_post(&mutex);
  printf("\nReader %d has left the database.\n",temp);  
  sleep(3);
}

void *writer_thr(int temp)
{

 printf("\nWriter %d is trying to enter database for modifying data",temp);
 sem_wait(&wrt);
 printf("\n Writer %d is writing in database.",temp);
 sleep(3);
 printf("\n Writer %d is leaving the database.\n",temp);
 sem_post(&wrt);
}
