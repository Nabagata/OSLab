#include<dirent.h>
#include<stdio.h>
#include<dirent.h>
char buffer[4096];

void ls(char* path, int argc, char*argv[])
{
        struct dirent *dp;
        DIR *dir=opendir(path);
        int flag=0;
        if(argc==2  && argv[1][1]=='a')
                flag=1;
        int c=0;
        while(dp=readdir(dir)){
                if(++c > (flag ? 0:2)){
                	printf("%s",dp->d_name);
                	printf(" ");
                }
        }
        closedir(dir);
        printf("\n");
}

void main(int argc, char **argv)
{
	char path[]="/Coding/OS";
	ls(path,argc,argv);
}
