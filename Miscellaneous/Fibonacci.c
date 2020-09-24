#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;

void* fibo(void* nums)
{
  int* dp=(int*)malloc((n+1)*sizeof(int));
  dp[0]=1; dp[1]=1;
  int i;
  
  for(i=2;i<=n;i++) dp[i]=dp[i-1]+dp[i-2];
  printf("%d ",dp[n]);
  return NULL;
}
 

int main(int argv,char** argc)
{
   pthread_t t1;
   int i;
   n=atoi(argc[1]);
     
   pthread_create(&t1,NULL,fibo,NULL);
   pthread_exit(NULL); 
   return 0;
}
   
