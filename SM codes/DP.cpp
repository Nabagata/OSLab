#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

sem_t chopstick[5];

void* dinein(void* a)
{
  int process=*(int*)a;
  do
  {
   sem_wait(&chopstick[process]);
   sem_wait(&chopstick[(process+1)%5]);
   cout<<"Philosopher "<<process<<" is eating: "<<endl;
   sem_post(&chopstick[(process+1)%5]);
   sem_post(&chopstick[process]);
  }while(true);
}

int main(int argc,char** argv)
{
  pthread_t phil[5];
  for(int i=0;i<5;i++) sem_init(&chopstick[i],0,1);

  for(int i=0;i<5;i++)
  {
   pthread_create(&phil[i],NULL,dinein,(void*)(&i));
  }
  for(int i=0;i<5;i++) pthread_join(phil[i],NULL);
 return 0;
} 
