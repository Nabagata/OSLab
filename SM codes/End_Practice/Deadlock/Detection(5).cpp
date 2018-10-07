#include<bits/stdc++.h>
#define m 3
#define n 5
using namespace std;

bool deadlock(int available[],int allocation[][m],int request[][m])
{
  int work[m];
  bool finish[n];
  memset(finish,false,sizeof(finish));
  for(int i=0;i<m;i++) 
  {
    work[i]=available[i];
    int j=0;
    for(;j<m;j++)
    {
      if(allocation[i][j]!=0) break;
    }
    if(j==n) finish[i]=true;
  }

  while(true)
  {
   int i=0; 
   for(;i<n;i++)
   {
     if(!finish[i])
     {
       //Check if "Need" of the process is less than the availability.
       int j=0;
       for(;j<m;j++)
       {
         if(request[i][j]>work[j]) break;
       }
       if(j!=m) continue;
       //This process has request<=work
       for(j=0;j<m;j++)  work[j]+=allocation[i][j];
       finish[i]=true; break;
      }
    }
    if(i==n)
    {
      for(int i=0;i<n;i++) 
      {
        if(!finish[i])       return false;
      }
      return true;
    }
  }
  return true;
}

int main(int argc,char** argv)
{
 int available[]={0,0,0};
 int allocation[][m]={{0,1,0}, 
		     {2,0,0},
                     {3,0,3},
                     {2,1,1},
                     {0,0,2}};
 int request[][m]={{0,0,0},
               {2,0,2},
               {0,0,1},
               {1,0,0},
               {0,0,2}};
 if(deadlock(available,allocation,request)) cout<<"No Deadlock"<<endl;
 else cout<<"Deadlock"<<endl;
 return 0;
}
 
