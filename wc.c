#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

char buffer[4096];
int wc(int argc,char *argv[]);
int main(int argc,char *argv[])
{
 return wc(argc,argv);
}
int wc(int argc,char *argv[])
{
 int fd;
 int i,j;
 int l,w,c;
 int tl,tw,tc;
 char ch;
 char t='a';
 int count,stop=0;
 if(argc<2)
 {
  l=w=c=0;
  while((ch=getchar())!= -1)
   {
     if(ch=='0') break;
     c++;
     if(isspace(ch))
     {
        while(isspace(ch))
        {
         if(ch=='\n') l++;
         if((ch=getchar())== (-1))
         {
          stop=1;break;
          }
         else c++;
        }
        if(!isspace(t)) w++;
        t=ch;
     }
   }
   printf("%d\t%d\t%d\n",l,w,c);
   return 0;
 }
 tl=tw=tc=0;
 for(int i=1;i<argc;i++)
 {
  
  fd=open(argv[i],O_RDONLY,0);
  if(fd<0)
  { 
   sprintf(buffer,"Error In Opening",argv[i]);
   perror(buffer);
   continue;
  }
  l=w=c=0;
  while((count=read(fd,buffer,sizeof(buffer)))>0)
  {
   c+=count;
   for(j=0;j<count;j++)
   {
     if(isspace(buffer[j]))
     {
      while(isspace(buffer[j]))
        {
         if(buffer[j]=='\n') l++;
         j++;
        } 
        if(!isspace(t)) w++;
        t=buffer[j];
     }   
   }
   }
  close(fd);
  printf("%s\t%d\n",argv[i],l);
  //tl+=l;
  //tw+=w;
  //tc+=c;
  //printf("%d\t%d\t%d\n",tl,tw,tc);
  return 0;
 }
}




