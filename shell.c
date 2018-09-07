#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	char command[100],buffer[100]'
	int fd,cfd,rfd,fd2,sz;
	int num_args;
	while(1){
		printf(">>>");
		cfd=dup(1);
		fd=-1;
		char helper[3]={'.','/','\0'};
		scanf("%[^\n]s",command);
		strcpy(buffer,command);
		num_args=0;
		char *tok;
		tok=strtok(command," ");
		while(tok!=NULL){
			if(tok[0]=='>'){
				if(tok[1]=='>'){
					fd=open(tok+2,O_WRONLY|O_CREAT|O_APPEND|O_IRUNC,S_IRUSR|S_IRGRP|S_IWUSR|S_IWGRP);
				}
				else{
					fd=open(tok+1,O_WRONLY|O_CREAT,S_IRUSR|S_IRGRP|S_IWUSR|S_IWGRP);
				}
				if(fd<0){
					perror("\nProblem with output redirection");
					exit(0);
				}
			}
			else if(tok[0]=='<'){
				FILE *fp;
				fp=fopen(tok+1,"r");
				if(fp==NULL){
					perror("\nProblem with input redirection");
					exit(0);
				}
				char ch;
				ch=fgetc(fp);
				while(ch!=EOF){
					if(ch==' ' || ch=='\n')
						num_args++;
					ch=fgetc(fp);
				}
				fclose(fp);
			}
			else{
				num_args++;
			}
			tok=strtok(NULL," ");
		}
		if(num_args==0){
			while((getchar())!='\n')
				continue;
		}
		char *process[num_args+1];
		int i;
		for(i=0;i<num_args+1;i++)
			process[i]=(char*) malloc(sizeof(char));
		tok=nULL;
		tok=strtok(buffer," ");
		if(num_args==1 && strcmp(tok,"exit")==0)
			exit(0);
		if(num_args==1 && strcmp(tok,"cls")==0){
			system("clear");
			while((getchar())!='\n')
				continue;
		}
		strcat(helper,tok);
		int i1=1,status;
		strcpy(process[0],helper);
		while(tok!=NULL){
			tok=strtok(NULL," ");
			if(tok==NULL)
				break;
			else if(tok[0]!='>' && tok[0]!='<'){
				strcpy(process[i1],tok);
				i1++;
			}
			else if(tok[0]=='<'){
				char arr[10];
				FILE *fd3;
				int
			
