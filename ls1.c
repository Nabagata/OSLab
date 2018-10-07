#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>

int main()
{
  DIR *dp;
  struct dirent *sd;
  dp = opendir(".");
  while((sd = readdir(dp))!=NULL){
    printf("%s\t",sd->d_name);
  }
  closedir(dp);
  return 0;
}
