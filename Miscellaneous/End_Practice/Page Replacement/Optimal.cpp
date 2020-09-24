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
    int pos=0,maxi=INT_MIN;
    for(int k=0;k<frame.size();k++)
    {
     //For each check future
     int x=frame[k],cnt=0,p;
     for(p=i+1;p<20;p++)
     {
      if(arr[p]==x) break;
      ++cnt;
     }
     if(p==20) cnt=20;
     if(cnt>maxi)
     {
      maxi=cnt;
      pos=k;
     }     
    }
    //Replace at position pos
    int y=frame[pos];
    ispresent.erase(y);
    frame[pos]=arr[i];
    ispresent.insert(arr[i]);
   }
   pg++;
   print(frame);
  } 
  cout<<"Page Faults "<<pg<<endl;
 return 0;
} 
    
    
    
