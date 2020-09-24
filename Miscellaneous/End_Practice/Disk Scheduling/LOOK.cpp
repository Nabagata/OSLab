#include<bits/stdc++.h>
using namespace std;

void moveleft(int& head,int n,vector<int>& arr,int& move,int x)
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
}

void moveright(int& head,int n,vector<int>& arr,int& move,int x)
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
    moveleft(head,n,arr,move,x);
    moveright(head,n,arr,move,x);
  }
  else if(d=='r')
  {
    moveright(head,n,arr,move,x);
    moveleft(head,n,arr,move,x);
  }
  cout<<"Movements :"<<move<<endl;
 return 0;
}
