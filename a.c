#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	for(int i=0;i<3;i++)
	{
		printf("Hello Baccha\n");
		fork();
	}
return 0;
}
