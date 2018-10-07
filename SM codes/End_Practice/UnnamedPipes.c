#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>

#define buffer 25
int read1,write1;

int main(int argc,char** argv)
{
  int fd[2];
  pid_t pid;
  read1=0;
  write1=1;
  char writer[buffer]="Greetings";
  char reader[buffer];

  if(pipe(fd)==-1) 
  {
    fprintf(stderr,"Pipe Failed");
    return 1;
  }
  
  pid=fork();
  if(pid<0)
  {
    fprintf(stderr,"Process Failed");
    return 1;
  }
  if(pid>0)//Parent Process will write
  {
    close(fd[read1]);
    write(fd[write1],writer,strlen(writer)+1);
    printf("%s written to buffer\n ",writer);
    close(fd[write1]);
  }
  else //Child Process
  {
    close(fd[write1]);
    read(fd[read1],reader,buffer);
    printf("%s read from buffer\n",reader);
    close(fd[read1]);
  }
  return 0;
}
  
 
