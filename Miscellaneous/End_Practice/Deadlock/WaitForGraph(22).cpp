#include<bits/stdc++.h>
using namespace std;
int am[10][10],n;

void dfs(bool& flag,bool visit[],bool rec[],int i)
{
  visit[i]=true; rec[i]=true;
  for(int j=0;j<n;j++)
  {
   if(am[i][j]==1 && !visit[j]) { cout<<"Calling for "<<j<<endl; dfs(flag,visit,rec,j); }
   if(am[i][j]==1 && visit[j] && rec[j]) flag=true;
  }
  rec[i]=false;
}


int main(int argc,char** argv)
{
  n=atoi(argv[1]);
  int u,v;
  while(true)
  {
   cin>>u>>v;
   if(u==-1) break;
   am[u-1][v-1]=1;
  }
  bool visit[n],rec[n];
  memset(visit,false,sizeof(visit));
  memset(rec,false,sizeof(rec));
  //Check if there is a cycle
  bool flag;
  for(int i=0;i<n;i++)
  {
   flag=false;
   dfs(flag,visit,rec,i);
   memset(visit,false,sizeof(visit));
   memset(rec,false,sizeof(rec)); 
   if(flag) break;
  }
  if(flag) cout<<"Deadlock"<<endl;
  else cout<<"No Deadlock"<<endl;
  return 0;
}
