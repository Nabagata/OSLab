// #include<stdio.h>
// #include<unistd.h>
// #include<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/shm.h>
// #include <errno.h>
// #include <sys/ipc.h>

int count=0;
int mutex,empty,full,shmid,n;
int in=0,out=0;
int *buffer;

void wait(int semid)
{
  struct sembuf sb;
  sb.sem_num=0;
  sb.sem_op=-1;
  sb.sem_flg=0;
}

void signal(int semid)
{
  struct sembuf sb;
  sb.sem_num=0;
  sb.sem_op=1;
  sb.sem_flg=0;
}

int producer()
{
  while(1){
    wait(empty);
    wait(mutex);
    printf("Produced: %d\n",count);
    in = (in+1)%n;
    buffer[in]=count++;

    signal(mutex);
    signal(full);
    sleep(3);
  }
  exit(1);
}

int consumer()
{
  while(1){
    wait(full);
    wait(mutex);
    out = (out+1)%n;
    buffer[out];
    printf("Consumed: %d\n",buffer[out]);

    signal(mutex);
    signal(empty);
    sleep(1);
  }
  exit(1);
}

int main()
{
  // printf("Enter the size of buffer: \n");
  n=5;
  if((mutex=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1)
 {
  perror("\nFailed to create semaphore.");
  exit(0);
 }
 if((semctl(mutex,0,SETVAL,1))==-1)
 {
  perror("\nFailed to set value for the semaphore.");
  exit(0);
 }
 if((empty=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1)
 {
  perror("\nFailed to create semaphore.");
  exit(0);
 }
 if((semctl(empty,0,SETVAL,n))==-1)
 {
  perror("\nFailed to set value for semaphore.");
  exit(0);
 }
 if((full=semget(IPC_PRIVATE,1,0666|IPC_CREAT))==-1)
 {
  perror("\nFailed to create semaphore.");
  exit(0);
 }

 if((semctl(full,0,SETVAL,0))==-1)
 {
  perror("\nFailed to set value for the semaphore.");
  exit(0);
 }
 if((shmid=shmget(IPC_PRIVATE,n*sizeof(int),0666|IPC_CREAT))==-1)
 {
  perror("\nFailed to allocate shared memory.");
  exit(0);
 }
  buffer=(int*)shmat(shmid,(const void *)0,0);
  // printf("%d\n",buffer[0]);
  pid_t ret = fork();
  if(ret==0)
    consumer();
  else if(ret>0)
    producer();
  return 0;
}
