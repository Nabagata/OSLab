#include<bits/stdc++.h>
#define n 3
using namespace std;

void print(vector<pair<int,int> >& frame)
{
  cout<<"Frame now is: "<<endl;
  for(int i=0;i<frame.size();i++) cout<<frame[i].first<<" ";
  cout<<endl;
}

int main(int argc,char** argv)
{
  int arr[]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
  vector<pair<int,int> >frame;
  set<int>ispresent;
  int pg=0;
  for(int i=0;i<20;i++)
  {
   if(ispresent.find(arr[i])!=ispresent.end())
   {
      for(int k=0;k<frame.size();k++) 
      {
        if(arr[i]==frame[k].first)frame[k].second=i;
      } 
      print(frame); continue;
   }
   if(frame.size()<n)
   {
    frame.push_back(make_pair(arr[i],i));
    ispresent.insert(arr[i]); 
   }
   else
   {
    //Search one with oldest counter
    int maxi=INT_MAX,pos=0;
    for(int k=0;k<frame.size();k++)
    {
      if(frame[k].second<maxi)
      {
        maxi=frame[k].second;
        pos=k;
      }
    }
    pair<int,int> y=frame[pos];
    ispresent.erase(y.first);
    frame[pos]=make_pair(arr[i],i);
    ispresent.insert(arr[i]);
   }
   pg++;
   print(frame);
  } 
  cout<<"Page Faults "<<pg<<endl;
 return 0;
} 
    
    
    
