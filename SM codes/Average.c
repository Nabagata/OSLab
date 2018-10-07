#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double avg;
int maxi,mini,n;

void* calc_avg(void* arr)
{
  int* nums=(int*) arr;
  int sum=0,i;
  for(i=0;i<n;i++) sum+=nums[i];
  avg=(sum/n);
}

void* calc_max(void* arr)
{
  int* nums=(int*) arr;
  int maxi=nums[0],i;
  for(i=1;i<n;i++) 
  {
    if(maxi<nums[i]) maxi=nums[i];
  }
}

void* calc_min(void* arr)
{
  int* nums=(int*) arr;
  int mini=nums[0],i;
  for(i=1;i<n;i++) 
  {
    if(mini>nums[i]) mini=nums[i];
  }
}
  
  

int main(int argv,char** argc)
{
   pthread_t t1;
   int i;
   n=atoi(argc[1]);
   int* arr=(int*)malloc(n*sizeof(int));
   for(i=0;i<n;i++) arr[i]=atoi(argc[i+2]);
   
   pthread_create(&t1,NULL,calc_avg,(void*)arr);
   pthread_create(&t1,NULL,calc_max,(void*)arr);
   pthread_create(&t1,NULL,calc_min,(void*)arr);
   
   printf("Average is: %lf",avg);
   printf("Minimum is: %d",mini);
   printf("Maximum is: %d",maxi);
   pthread_exit(NULL);
   free(arr);
   return 0;
}
   
