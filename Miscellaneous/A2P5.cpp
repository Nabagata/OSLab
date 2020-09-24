#include <bits/stdc++.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
int arr[100];
map<int,int> m;
void check(int num)
{
	if(num==1)
	{
		cout<<num<<" is not prime\n";
		return;
	}
	for(int i=2;i<num;i++)
		if(num%i==0){
			cout<<num<<" is not prime\n";
			return ;
		}
	cout<<num<<" is  prime\n";
}

int main(int argc,char *argv[]){
	
	int i,num;
	int n=atoi(argv[1]);

	pid_t p[n];

	for(i=0;i<n;i++)
	{
		arr[i]=atoi(argv[i+2]);
		p[i]=fork();
		num=arr[i];
		if(p[i])
			sleep(1);
		else 
		if(p[i]==0)
		{
			check(num);
			break;
		}
		//while(wait(NULL)>0);
	}


}
