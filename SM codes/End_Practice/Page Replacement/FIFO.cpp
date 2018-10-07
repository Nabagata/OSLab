#include<bits/stdc++.h>
#define n 3
using namespace std;

void print(vector<int>& frame)
{
  cout<<"Frame now is: "<<endl;
  for(int i=0;i<frame.size();i++) cout<<frame[i]<<" ";
  cout<<endl;
}

int main(int argc,char** argv)
{
  int arr[]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
  vector<int>frame;
  set<int>ispresent;
  int pg=0,j=0;
  for(int i=0;i<20;i++)
  {
   if(ispresent.find(arr[i])!=ispresent.end())
   {
      print(frame); continue;
   }
   if(frame.size()<n)
   {
    frame.push_back(arr[i]);
    ispresent.insert(arr[i]); 
   }
   else
   {
    int x=frame[j];
    frame[j]=arr[i];
    ispresent.erase(x);
    ispresent.insert(arr[i]);
    j=(j+1)%n;
   }
   pg++;
   print(frame);
  } 
  cout<<"Page Faults "<<pg<<endl;
 return 0;
} 
    
    
    
