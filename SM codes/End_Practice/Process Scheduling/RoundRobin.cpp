#include<bits/stdc++.h>
#define quantum 4
using namespace std;

struct process
{
  int pid;
  int cpu_burst;
}; 

int main(int argc,char** argv)
{
  int n=atoi(argv[1]);
  cout<<"Enter the processes "<<endl;
  queue<process>q;
  for(int i=0;i<n;i++)
  {
    process p;
    p.pid=i+1;
    cin>>p.cpu_burst;
    q.push(p);
  }
  int cnt=0;
  while(!q.empty())
  {
    process p=q.front(); 
    q.pop();
    if(p.cpu_burst>quantum)
    {
      cout<<"Process "<<p.pid<<" executed from "<<cnt<<" to "<<cnt+quantum<<endl;
      cnt+=quantum;
      p.cpu_burst-=quantum;
      q.push(p);
    }
    else
    {
       cout<<"Process "<<p.pid<<" executed from "<<cnt<<" to "<<cnt+p.cpu_burst<<endl;
       cnt+=p.cpu_burst;
    }
  }
 return 0;
}







