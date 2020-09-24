#include<bits/stdc++.h>
using namespace std;

int main(int argc,char** argv)
{
  int head,n;
  cout<<"Enter current head position"<<endl;
  cin>>head;
  cout<<"Enter n"<<endl;
  cin>>n;
  int arr[n];
  bool visit[n];
  memset(visit,false,sizeof(visit));
  for(int i=0;i<n;i++) cin>>arr[i];
  int move=0;
  for(int i=0;i<n;i++)
  {
    int mini=INT_MAX,pos=0;
    for(int j=0;j<n;j++)
    {
      if(mini>abs(head-arr[j]) && !visit[j])
      {
        mini=abs(head-arr[j]); pos=j;
      }
    }
    visit[pos]=true;
    move+=abs(head-arr[pos]);
    cout<<"Head at: "<<arr[pos]<<endl;
    head=arr[pos];
  }
  cout<<"Movements :"<<move<<endl;
 return 0;
}
