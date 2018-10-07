#include<bits/stdc++.h>
using namespace std;

void moveleft(int& head,int n,vector<int>& arr,int& move,int flag,int x)
{
  int i=0; 
  for(;i<n;i++) 
  {
   if(arr[i]>x) break;
  }
  i--;
  for(;i>=0;i--)
  {
    move+=abs(head-arr[i]);
    cout<<"Head at "<<arr[i]<<endl;
    head=arr[i];
  }
  if(!flag)//For d='l' case
  {
    move+=head;
    cout<<"Head at 0"<<endl;
    head=0;
  }  
}

void moveright(int& head,int n,vector<int>& arr,int& move,int flag,int x)
{
  int i=0;
  for(;i<n;i++) 
  {
   if(arr[i]>x) break;
  }
  
  for(;i<n;i++)
  {
    move+=abs(head-arr[i]);
    cout<<"Head at "<<arr[i]<<endl;
    head=arr[i];
  }
  if(!flag)//For d='r' case
  {
    move+=abs(head-199);
    cout<<"Head at 199"<<endl;
    head=199;
  }  
}



int main(int argc,char** argv)
{
  int head,n,move=0; char d;
  cout<<"Enter current head position"<<endl;
  cin>>head;
  cout<<"Enter n"<<endl;
  cin>>n;
  vector<int>arr(n);
  for(int i=0;i<n;i++) cin>>arr[i];
  cout<<"Enter direction "<<endl;
  cin>>d;
  sort(arr.begin(),arr.end());
  int x=head;
  if(d=='l')
  {
    moveleft(head,n,arr,move,0,x);
    moveright(head,n,arr,move,1,x);
  }
  else if(d=='r')
  {
    moveright(head,n,arr,move,0,x);
    moveleft(head,n,arr,move,1,x);
  }
  cout<<"Movements :"<<move<<endl;
 return 0;
}
