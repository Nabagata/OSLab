#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>
using namespace std;

sem_t write,mutex;
int cnt=0,var=0;

struct edge
{
 int process;
int m;
};

void Writer(void* a)
{
  edge e=*(edge*)a;
  sem_wait(&write);
  int var=rand()%100;
  cout<<e.process<<" is writing "<<var<<endl;
  sem_post(&write);
} 

void Reader(void* a)
{
  edge e=*(edge*)a;
  sem_wait(&mutex);
  cnt++;
  if(cnt>=1) sem_wait(&write);//Only 1 writer active at a time
  sem_post(&mutex);

  cout<<e.process<<" is reading "<<var<<endl;

  sem_wait(&mutex);
  --cnt;
  if(cnt==0) sem_post(&write);
  sem_post(&mutex);
}

int main(int argc,char** argv)
{
  srand(time(NULL));
  int n=atoi(argv[1]);//No. of Readers and Writers
  sem_init(&write,0,1);
  sem_init(&mutex,0,1);
  pthread_t reader[n],writer[n];
  edge e[n];
  
  for(int i=0;i<n;i++)
  {
   e[i].process=i+1; e[i].m=i;
   pthread_t(&reader[i],NULL,Reader,e+i);
   pthread_t(&writer[i],NULL,Writer,e+i);
  }
  
  for(int i=0;i<n;i++)
  {
    pthread_join(reader[i],NULL);
    pthread_join(writer[i],NULL);
  }
 return 0;
}
  
