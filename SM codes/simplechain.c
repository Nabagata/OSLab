#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char** argv)
{
  pid_t childpid=0;
  int i,n,j;
  
  if(argc<2) //Checking for valid Number of command-Line Arguments.
  {
    fprintf(stderr,"Usage: %s processes\n",argv[0]);
    return 1;
  }
  
  n=atoi(argv[1]);
  for(i=1;i<=n;i++)
  {
    if(childpid=fork()) break;    
  }
  int k=atoi(argv[2]),m=atoi(argv[3]);
  for(j=1;j<=k;j++)
  {
    printf("i:%d process ID:%ld parentID:%ld child ID:%ld\n",i, (long)getpid(),(long)getppid(), (long)childpid); 
    sleep(m);
  }
  wait();
  return 0;
}
