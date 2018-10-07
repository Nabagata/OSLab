#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;

bool isPrime(int x)
{
  for(int i=2;i*i<=x;i++)
  {
    if(x%i==0) return false;
  }
  return true;
}

void* prime_print(void* nums)
{
  for(int i=2;i<=n;i++)
  {
    if(isPrime(i)) printf("%d ",i);
  } 
  return NULL;
}  

int main(int argv,char** argc)
{
   pthread_t t1;
   int i;
   n=atoi(argc[1]);
     
   pthread_create(&t1,NULL,prime_print,NULL);
   pthread_exit(NULL); 
   return 0;
}
   
