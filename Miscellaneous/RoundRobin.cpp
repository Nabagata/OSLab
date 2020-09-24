#include<bits/stdc++.h>
using namespace std;

struct process
{
  int pid;
  int cpu_burst;
};

int main(int argc,char** argv)
{
  int n=atoi(argv[1]); 
  process p;
  int counter=0,time_slice; 
  queue<process>q;
  for(int i=0;i<n;i++)
  {
    cin>>p.pid;
    cin>>p.cpu_burst;
    q.push(p);
  }
  cin>>time_slice;
  while(!q.empty())
  {
    process l=q.front();
    if(l.cpu_burst-time_slice>0)  
    {
      cout<<" Process "<<l.pid<<" running from: "<<counter<<" to "<<counter+time_slice<<endl;
      counter+=time_slice;
    }
    else 
    { 
      cout<<" Process "<<l.pid<<" running from: "<<counter<<" to "<<counter+l.cpu_burst<<endl;
      counter+=l.cpu_burst;
    }    
    l.cpu_burst-=time_slice;
    q.pop();    
    if(l.cpu_burst>0) q.push(l);    
  } 
return 0;
} 
