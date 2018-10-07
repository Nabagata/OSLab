#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int n;
int mutex,custc;
int *front,*rear,*ARR,shm,f,r;
int *cid,c;
void sem_lock(int semid)
{ 
 struct sembuf sb;
 sb.sem_num=0;
 sb.sem_op=-1;
 sb.sem_flg=0;
 if((semop(semid,&sb,1))==-1)    
 {
  perror("\nFailed to acquire semaphore.");
  exit(0);
 }
}

void sem_unlock(int semid)
{
 struct sembuf sb;
 sb.sem_num=0;
 sb.sem_op=1;
 sb.sem_flg=0;
 if((semop(semid,&sb,1))==-1)    
 {
  perror("\nFailed to release semaphore.");
  exit(0);
 }
}
void barber(int id)
{
 while(1)
 {   
  if(*front==*rear)
  {
   printf("barber is going to sleep\n");
   sem_lock(custc);//sleeping 
  }     
  sem_lock(mutex);/*P(mutex)*/
  
  printf("Barber %d is cutting hair of customer :%d.\n",id,ARR[*front]);
  //sleep(2);
  *front=(*front+1)%10;
  sem_unlock(mutex);//releas witing for customer
  //sleep(1);   
 }
 exit(1);
}
void *customer(int id)
{
 while(1)
 {
  
  sem_lock(mutex);/*P(mutex)*/
  
  (*cid)++;
  if((*rear+1)%10!=*front)
  {
   ARR[*rear]=*cid;
   printf("Customer  %d  occupied %d seat number \n",ARR[*rear],*rear);
   *rear=(*rear+1)%10;
   sleep(2);
   sem_unlock(mutex);//release waiting for mutex
   if((*front+1)%10==*rear)
   {
    sem_unlock(custc);
    printf("waking up barber\n");
   }
  }
  else
  {
   printf("comming customer %d is leaving bcs of full\n",*cid);
   sleep(2);
   sem_unlock(mutex);

  }
  sleep(10);
 }
 exit(id);
}
int main()
{
 n=10;
 if((mutex=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1)
 {
  printf("error in creation of semaphore\n");
  exit(1);
 }
 if((semctl(mutex,0,SETVAL,1))==-1)
 {
  printf("erroe in settting value\n");
  exit(1);
 }
 if((custc=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1)
 {
  printf("error in creation of semaphore\n");
  exit(1);
 }
 if((semctl(custc,0,SETVAL,1))==-1)
 {
  printf("erroe in settting value\n");
  exit(1);
 }
 if((shm=(shmget(IPC_PRIVATE,n*sizeof(int),0666|IPC_CREAT)))==-1)
 {
  printf("error in creation of shared memory\n");
  exit(1);
 }
 ARR=(int *)shmat(shm,(void *)0,0);
 if((f=(shmget(IPC_PRIVATE,sizeof(int),0666|IPC_CREAT)))==-1)
 {
  printf("error in creation of shared memory\n");
  exit(1);
 }
 if((r=(shmget(IPC_PRIVATE,sizeof(int),0666|IPC_CREAT)))==-1)
 {
  printf("error in creation of shared memory\n");
  exit(1);
 }
 if((c=(shmget(IPC_PRIVATE,sizeof(int),0666|IPC_CREAT)))==-1)
 {
  printf("error in creation of shared memory\n");
  exit(1);
 }
 cid=(int *)shmat(c,(void *)0,0);
 front=(int *)shmat(f,(void *)0,0);
 rear=(int *)shmat(r,(void *)0,0);
 int k,i;
 for(i=0;i<n;i++)
 {
  k=fork();
  if(k==0)
   customer(i+1);
 }
 barber(1);
 exit(0);
}
