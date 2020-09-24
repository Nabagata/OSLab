#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>

int main(int argc,char** argv)
{
  int segment_id=0;
  char* shared_memory;
  const int size=4096;

  //Allocate the segment
  segment_id=shmget(IPC_PRIVATE,size,S_IRUSR|S_IWUSR);
  //Attach to shared_memory
  shared_memory=(char*)shmat(segment_id,NULL,0);
  
  sprintf(shared_memory,"Greetings");
  printf(shared_memory);
  
  //Detach
  shmdt(shared_memory);
  //Deallocate
  shmctl(segment_id,IPC_RMID,NULL);
  return 0;
}
