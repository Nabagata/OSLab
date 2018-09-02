#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int cat(int args,char *argv[]);
char buffer[4096];
void main(int argc,char *argv[])
{
 return cat(argc,argv);
}

int cat(int argc,char *argv[])
{
 int i,j;
 int fd,count;
 if(argc==1)
 {
  while(fgets(buffer,4096,stdin)!=NULL)
   fputs(buffer,stdout); 
 }
 for(i=1;i<argc;i++)
 {
  if(strcmp(argv[i],"-")==0)
   fd=fileno(stdin);
  else
   fd=open(argv[i],O_RDONLY,0);
  if(fd<0)
  {
   sprintf(buffer,"Error opening file :",argv[i]);
   perror(buffer);
   continue;
  }
  while((count=read(fd,buffer,sizeof(buffer)))>0)
  {
     write(fileno(stdout),buffer,count);
  }
  if(strcmp(argv[i],"-")!=0)
   close(fd);
 }
 return 0;
}


			
			
		
