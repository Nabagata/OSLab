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
	

int main()
{

	funx(3);
}
	
