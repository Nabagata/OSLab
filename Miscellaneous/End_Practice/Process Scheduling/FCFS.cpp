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
  vector<process>v;
  int cnt=0;
  for(int i=0;i<n;i++)
  {
    process p;
    cin>>p.cpu_burst;
    p.pid=i+1;
    v.push_back(p);
  }
  cout<<"The processes are executed as follows: "<<endl;
  int i=0;
  while(i<n)
  {
    cout<<v[i].pid<<" executing from "<<cnt<<" to "<<cnt+v[i].cpu_burst<<endl;
    cnt+=v[i].cpu_burst;
    ++i;
  }
  return 0;
}






