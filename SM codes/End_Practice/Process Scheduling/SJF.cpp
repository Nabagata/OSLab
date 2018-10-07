#include<bits/stdc++.h>
using namespace std;

struct process
{
  int pid;
  int cpu_burst;
};

bool mycomp(process a,process b)
{
  return (a.cpu_burst<b.cpu_burst);
}

int main(int argc,char** argv)
{
  int n=atoi(argv[1]);
  cout<<"Enter the processes"<<endl;
  vector<process>v;
  for(int i=0;i<n;i++)
  {
    process p;
    cin>>p.cpu_burst;
    p.pid=i+1;
    v.push_back(p);
  }

  int cnt=0;
  sort(v.begin(),v.end(),mycomp);

  for(int i=0;i<n;i++)
  {
   cout<<v[i].pid<<" running from "<<cnt<<" to "<<cnt+v[i].cpu_burst<<endl;
   cnt+=v[i].cpu_burst;
  }
  return 0;
}
  
