#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

void rm(int argc,char * argv[]);
char buffer[4096];
void main(int argc,char *argv[])
{
 if(argc!=2)
  printf("Usage:./a.out [Filename][Folder]\n");
 else
  rm(argc,argv);  
}
void remfiles(char *ar)
{
 struct dirent *dp;
 DIR *dir=opendir(ar);
 int c=0,x;
 char ch[1];
 ch[0]='/';
 while(dp=readdir(dir))
 {
  if(++c>2)
  {
   char fl[strlen(ar)];
   for(int i=0;i<strlen(ar);i++)
    fl[i]=ar[i];
   strcat(fl,dp->d_name);
   if(remove(fl)!=0)
     remfiles(fl);
  }
  }
 closedir(dir);
 if(remove(ar)!=0)
  printf("Could Not delete\n");
}
void rm(int argc,char * argv[])
{
 if(remove(argv[1])!=0)
 remfiles(argv[1]); 
}



