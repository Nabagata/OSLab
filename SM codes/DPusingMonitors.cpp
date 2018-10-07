#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

sem_t self[5];
sem_t mutex;
class monitor
{
  public: 
        enum {THINKING,HUNGRY,EATING}state[5];
	
  void pickup(int i)
  {
   sem_wait(&mutex);
   printf("%d is hungry: \n",i);
   state[i]=HUNGRY;
   test(i);
   if(state[i]!=EATING) sem_wait(&self[i]);
   sem_post(&mutex);
  }

  void putdown(int i)
  {
   sem_wait(&mutex);
   state[i]=THINKING;
   test((i+4)%5);
   test((i+1)%5);
   sem_post(&mutex);
  }

  void test(int i)
  {
    if(state[(i+1)%5]!=EATING && state[(i+4)%5]!=EATING && state[i]==HUNGRY)
    {
      printf("%d is eating: \n",i);
      state[i]=EATING;
      sem_post(&self[i]);
    }
  }
}M;

void* init(void* a)
{
  int obj=*((int*)a);
  M.pickup(obj);
  sleep(3);
  M.putdown(obj);
}

int main(int argc,char** argv)
{
  pthread_t phil[5];
  sem_init(&mutex,0,1);
  for(int i=0;i<5;i++) sem_init(&self[i],0,1);
  int p[5];
  for(int i=0;i<5;i++) 
  {
    p[i]=i;
    pthread_create(&phil[i],NULL,init,p+i);
  }

  for(int i=0;i<5;i++) pthread_join(phil[i],NULL);
}

  
