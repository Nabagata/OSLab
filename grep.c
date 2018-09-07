#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
char buffer[4096];

int matchPattern(int beg, int end, char *pat)
{
	int j=0,sz=strlen(pat),prev;
	for(int i=beg;i<end;i++){
		if(j==sz)
			return 1;
		if(buffer[i]==pat[j]){
			if(j==0){
				prev=i;
				j++;
			}
			else{
				if(j!=0){
					i=prev;
					j=0;
				}
			}
		}
	}
	return 0;
}	

void grep(int argc, char*argv[])
{
	if(argc==1){
		int fd;
		fd=open(argv[2],O_RDONLY,0);
		if(fd<0){
			perror("Error");
			exit(1);
		}
		int cat=read(fd,buffer,sizeof(buffer));
		int a[4096],c=1;
		a[0]=0;
		for(int i=0;i<cnt;i++){
			if(buffer[i]=='\n')
				a[c++]=i;
		}
		close(fd);
		for(int i=0;i<c-i;i++){
			if(matchPattern(a[i],a[i+1],argv[i]){
				for(int j=a[i];j<a[i+1];j++)
					printf("%c",buffer[i]);
			}
		}
	else{
		printf("%d",[pattern][filename]);
	printf("\n");
}
