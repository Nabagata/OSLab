#include<bits/stdc++.h>
using namespace std;


struct process
{
  int id;
  int cpu_burst;
  int arrival;
};

bool comp(process a,process b)
{
  return (a.arrival<b.arrival);
}

struct hascomp
{
 bool operator()(process& a,process& b)
 {
   return (a.cpu_burst>b.cpu_burst);
 }
};

int main(int argc,char** argv)
{
  int n=atoi(argv[1]);
  vector<process>q;
  for(int i=0;i<n;i++)
  {
   process x;
   cin>>x.cpu_burst;
   cin>>x.arrival;
   x.id=i+1;
   q.push_back(x);
  }

  sort(q.begin(),q.end(),comp);
  int j=0;
  priority_queue<process,vector<process>,hascomp>pq;
  int cnt=0;
  pq.push(q[j++]);
  while(j<n)
  {
    if(!pq.empty()) cout<<"Process "<<pq.top().id<<" executing at "<<cnt<<endl;
    else cout<<"Cpu is idle at "<<cnt<<endl;

    if(q[j].arrival>cnt)
    {
      process p=pq.top();
      pq.pop();
      p.cpu_burst--;
      if(p.cpu_burst>0) pq.push(p); ++cnt;
    }

    if(q[j].arrival==cnt) pq.push(q[j++]);
  }

  while(!pq.empty())
  {
    cout<<"Process "<<pq.top().id<<" executing at "<<cnt<<endl;
    process p=pq.top();
    pq.pop();
    p.cpu_burst--;
    if(p.cpu_burst>0) pq.push(p);
    ++cnt;
  }
 return 0;
}




