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
  for(int i=0;i<n;i++) cin>>arr[i];
  int move=0;
  for(int i=0;i<n;i++)
  {
   cout<<"Head at "<<arr[i]<<endl;
   move+=abs(arr[i]-head);
   head=arr[i];
  }
  cout<<"Movements :"<<move<<endl;
 return 0;
}
