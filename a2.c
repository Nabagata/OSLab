#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int funx(int n)
{
		if(n==0)
		return 0;

		int pid=fork(),ppid;
	
		if(pid==0)
		{
		  pid=getpid();
		  ppid=getppid();
		  printf("%d",pid);
		  printf("\n");
		  printf("%d",ppid);
		  printf("\n\n");
		  funx(n-1);
		}
}
	

int main(int arg, char** s)
{
	int noc=0,i=0;
	char* num=s[1];
	
	while(num[i]!='\0')
	{
		noc*=10;
		noc+=(int)(num[i])-48;
		i++;
	}

	funx(noc);
}
	
