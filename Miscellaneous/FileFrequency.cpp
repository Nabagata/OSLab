#include <bits/stdc++.h>
#include <fstream>
#include <pthread.h>
using namespace std;
map<string,int>m;

void* count(void* ch)
{
    char* s1=(char*)ch;
    string s(s1); 
    string tmp="";
    for(int i=0;i<s.length();i++)
    {
      char c=s.at(i);
      if(c!=' ') tmp+=c;
      else
      {
        m[tmp]++;
        tmp="";
      }
    }  
}

int main(int argc,char* argv)
{
  fstream fin;
  int n,j=0;
  cin>>n;
  pthread_t t1[n];
  fin.open("File1.txt");
  string s="";
  while(fin)
  {
    getline(fin,s);
    m.clear();
    s+=" ";
    char* ch=s.c_str();
    pthread_create(&t1[j],NULL,count,(void*)ch);
    j=(j+1)%n;
    pthread_join(t1[j],NULL);  
    s=""; 
  }

  for(map<string,int>::iterator it=m.begin();it!=m.end();it++) cout<<it->first<<" "<<it->second<<endl;
  fin.close();
return 0;
}


