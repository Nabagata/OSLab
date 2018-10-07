#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>
using namespace std;

int front=0,rear=0;
int buffer[100];
sem_t mutex,full,empty;

struct process
{
  int n1;
  int pid;
};

void* Producer(void* a)
{
  process p=*(process*)a;
  int s_ize=p.n1;
  sem_wait(&empty);
  sem_wait(&mutex);
  buffer[rear]=rand()%100;
  cout<<"Process "<<p.pid<<" writing "<<buffer[rear]<<" at "<<rear<<endl;
  rear=(rear+1)%s_ize;
  sem_post(&mutex);
  sem_post(&full);
}

void* Consumer(void* a)
{
  process p=*(process*)a;
  int s_ize=p.n1;
  sem_wait(&full);
  sem_wait(&mutex);
  cout<<"Process "<<p.pid<<" reading "<<buffer[front]<<" at "<<front<<endl;
  front=(front+1)%s_ize;
  sem_post(&mutex);
  sem_post(&empty);
}
 

int main(int argc,char** argv)
{
  srand(time(NULL));
  sem_init(&mutex,0,1);
  sem_init(&empty,0,atoi(argv[1]));
  sem_init(&full,0,0);
  int n=atoi(argv[2]);
  
  pthread_t producer[n],consumer[n];
  process p[n];
  
  for(int i=0;i<n;i++)
  {
    p[i].pid=i+1;
    p[i].n1=atoi(argv[1]);
    pthread_create(&producer[i],NULL,Producer,p+i);
    pthread_create(&consumer[i],NULL,Consumer,p+i);
  }

  for(int i=0;i<n;i++)
  {
    pthread_join(producer[i],NULL);
    pthread_join(consumer[i],NULL);
  }
  return 0;
}













