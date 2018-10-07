#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>
using namespace std;

int front=0,rear=0;
sem_t mutex,empty,full;
int buffer[100];

struct edge
{
  int n1;
  int process;
};

void* Producer(void* a)
{
  edge e=*(edge*)a;
  int size=e.n1;
  sem_wait(&empty);
  sem_wait(&mutex);
  buffer[rear]=rand()%100;
  cout<<"Producer "<<e.process<<" producing "<<buffer[rear]<<" at position: "<<rear<<endl;
  rear=(rear+1)%size;
  sem_post(&mutex);
  sem_post(&full);
}

void* Consumer(void* a)
{
  edge e=*(edge*)a;
  int size=e.n1;
  sem_wait(&full);
  sem_wait(&mutex);
  cout<<"Consumer "<<e.process<<" is consuming "<<buffer[front]<<" at position: "<<front<<endl;
  front=(front+1)%size;
  sem_post(&mutex);
  sem_post(&empty);
}
  

int main(int argc,char** argv)
{
  sem_init(&mutex,0,1);
  sem_init(&empty,0,atoi(argv[1]));
  sem_init(&full,0,0);

  int n=atoi(argv[2]);
  pthread_t producer[n],consumer[n];
  edge e[n];
  for(int i=0;i<n;i++)
  {
    
    e[i].n1=atoi(argv[1]);
    e[i].process=i;
    pthread_create(&producer[i],NULL,Producer,e+i);
    pthread_create(&consumer[i],NULL,Consumer,e+i);
  }

  for(int i=0;i<n;i++)
  {
   pthread_join(producer[i],NULL);
   pthread_join(consumer[i],NULL);
  }
  return 0;
}
