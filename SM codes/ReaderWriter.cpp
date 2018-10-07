#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>
using namespace std;

sem_t mutex,write;
int cnt=0,data;

void* Writer(void* a)
{
  int process=*(int*)a;
  sem_wait(&write);
  data=rand()%20+1;
  cout<<"Writer "<<process<<" is writing "<<data<<endl;
  sem_post(&write);
}

void* Reader(void* a)
{
  int process=*(int*)a;
  sem_wait(&mutex);
  cnt++;
  if(cnt==1) sem_wait(&write);
  sem_post(&mutex);
  //Critical Section begins  
  cout<<"Reader "<<process<<" is reading: "<<data<<endl;
  //Critical Section ends 
  
  sem_wait(&mutex);
  cnt--;
  if(cnt==0) sem_post(&write);
  sem_post(&mutex);
}

int main(int argc,char** argv)
{
  int r=atoi(argv[1]);//Input the Number of Reader Writer threads
  long reader[r],writer[r];
  //srand(NULL);

  sem_init(&mutex,0,1);
  sem_init(&write,0,1);

  pthread_t read[r],write[r];

  for(int i=0;i<r;i++)
  {
    reader[i]=i;
    writer[i]=i;
    pthread_create(&read[i],NULL,Reader,reader+i);
    pthread_create(&write[i],NULL,Writer,writer+i);
  }

  for(int i=0;i<r;i++)
  {
   pthread_join(read[i],NULL);
   pthread_join(write[i],NULL);
  }
return 0;
}

