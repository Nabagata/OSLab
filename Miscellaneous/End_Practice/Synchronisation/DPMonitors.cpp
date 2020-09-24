#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/types.h>
using namespace std;

sem_t self[5];
enum {HUNGRY,EATING,THINKING}state[5];

void test(int i)
{
  if(state[i]==HUNGRY && state[(i+1)%5]!=EATING && state[(i+4)%5]!=EATING)
  {
   state[i]=EATING; 
   sem_post(&self[i]);
   printf("%d is eating\n",i);
  }
}

void pickup(int i)
{
  printf("%d is hungry\n",i);
  state[i]=HUNGRY;
  test(i);
  if(state[i]!=EATING) sem_wait(&self[i]);
}

void putdown(int i)
{
  printf("%d is done eating\n",i);
  state[i]=THINKING;
  test((i+1)%5);
  test((i+4)%5);
}

void initial(void* a)
{
  int p=*(int*)a;
  pickup(p);
  sleep(3);
  putdown(p);
} 


int main(int argc,char** argv)
{
  pthread_t phil[5];
  for(int i=0;i<5;i++) 
  {
    sem_init(&self[i],0,1);
    state[i]=THINKING;
  }
  int ph[5];
  for(int i=0;i<5;i++) 
  {
    ph[i]=i;
    pthread_create(&phil[i],NULL,initial,ph+i);
  }

  for(int i=0;i<5;i++) pthread_join(phil[i],NULL);
  return 0;
}
