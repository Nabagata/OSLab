#include<bits/stdc++.h>
#define m 3
#define n 5
using namespace std;

void calcneed(int allocation[][m],int maxi[][m],int need[][m])
{
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++) need[i][j]=maxi[i][j]-allocation[i][j];
  }
}

bool isSafe(int available[],int allocation[][m],int need[][m])
{
  int work[m];
  int finish[n];
  memset(finish,0,sizeof(finish));
  for(int i=0;i<m;i++) work[i]=available[i];
  int s=0;
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
         if(need[i][j]>work[j]) break;
       }
       if(j!=m) continue;
       //This process has need<=work
       for(j=0;j<m;j++)  work[j]+=allocation[i][j];
       finish[i]=s++; break;
      }
    }
    if(i==n)
    {
      for(int i=0;i<n;i++) 
      {
        if(!finish[i]) return false;
      }
      cout<<"The safe sequence is: "<<endl;
      for(int i=0;i<n;i++) cout<<finish[i]<<" ";
      cout<<endl;
      return true;
    }
  }
  return true;
}

void resource_request(int p,int allocation[][m],int request[],int max[][m],int need[][m],int available[])
{
  for(int i=0;i<m;i++)
  {
    if(request[i]>need[p][i]) 
    {
     cout<<"Request cannot be granted. Over-expecting! "<<endl;
     return;
    }
  }
  for(int i=0;i<m;i++)
  {
    if(request[i]>available[i]) 
    {
     cout<<"Request cannot be granted immediately. Wait for sometime!"<<endl; 
     return;
    }
  }
  //Try out the psuedo allocation and check for deadlock
  for(int i=0;i<m;i++)
  {
    available[i]-=request[i];
    allocation[p][i]+=request[i];
    need[p][i]-=request[i];
  }  
  if(isSafe(available,allocation,need))//Allocation done without deadlock
  {
   cout<<"Allocation successful"<<endl;
   return;
  }   
  cout<<"Allocation not successful"<<endl; 
  for(int i=0;i<m;i++)
  {
    available[i]+=request[i];
    allocation[p][i]-=request[i];
    need[p][i]+=request[i];
  }
}

int main(int argc,char** argv)
{
 int available[]={3,3,2};
 int allocation[][m]={{0,1,0}, 
		     {2,0,0},
                     {3,0,2},
                     {2,1,1},
                     {0,0,2}};
 int maxi[][m]={{7,5,3},
               {3,2,2},
               {9,0,2},
               {2,2,2},
               {4,3,3}};
 int need[n][m];
 calcneed(allocation,maxi,need);//Need at the current instance
 int request[m]; int x;
 cout<<"Enter the current request"<<endl;
 cin>>x;
 for(int i=0;i<m;i++) cin>>request[i];
 resource_request(x,allocation,request,maxi,need,available);
 return 0;
}
 





