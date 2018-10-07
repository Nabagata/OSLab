#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>
using namespace std;

sem_t chopstick[5];

void eating(void* a)
{
  int i=*(int*)a;
  do
  {
   sem_wait(&chopstick[i]);
   sem_wait(&chopstick[(i+1)%5]);
   cout<<"Philosopher "<<i<<" is eating "<<endl;
   sem_post(&chopstick[(i+1)%5]);
   sem_post(&chopstick[i]);
  }while(true);
}

int main(int argc,char** argv)
{
  for(int i=0;i<5;i++) sem_init(&chopstick[i],0,1);
  pthread_t phil[5];
  for(int i=0;i<5;i++)
  {
   pthread_create(&phil[i],NULL,eating,(void*)(&i));
  }
  for(int i=0;i<5;i++) pthread_join(phil[i],NULL);
 return 0;
} 
