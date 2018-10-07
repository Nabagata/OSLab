#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum=0,n,p;
void* check(void* arr)
{
  int* nums=(int*) arr;
  int i=0;
  for(;i<(n/p);i++)
  {
    if(n%nums[i]==0) sum+=nums[i];
  }
  return NULL;
}

int main(int argv,char** argc)
{
   int i,j=1,k;
   n=atoi(argc[1]);
   p=atoi(argc[2]);
   pthread_t t1[p];
   
   int* arr=(int*)malloc((n/p)*sizeof(int));
   for(i=1;i<=p;i++) 
   {   
      k=0;
      for(;k<(n/p);k++) 
      { 
       arr[k]=j; ++j; if(j>=n) break; 
       printf("%d ",arr[k]);
      }
      printf("\n"); 
      pthread_create(&t1[i],NULL,check,(void*)arr); 
      if(j>=n) break; 
      printf("%d\n",sum);
   }
   if(sum==n) printf("true\n");
   else printf("false\n");
   pthread_exit(NULL); 
   free(arr);
   return 0;
}
   
