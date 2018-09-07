#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>


int main()
{
     char command_ip[2048];                                      //input command from user
     char buffer[2048];                                          //buffer to store a copy of the "command_ip"
     int fd, cfd;                                                //file descriptors
     int num_of_args = 0;                                        //no of arguments in "command_ip"

     while(1)
     {
          printf(">>>");                                         //to give a shell alike look
          cfd = dup(1);                                          //to create copy of file descriptor

          strcpy(command_ip, "");
          fd = -1;
          scanf("%[^\n]s", command_ip);                          //read input from the screen untill a '\n' is recieved
          //printf("%s", command_ip);

          strcpy(buffer, command_ip);                            //copying the command_ip to buffer

          char *word;                                            //to store word by word from input string

          word = strtok(command_ip, " ");                        //get the first word
          //strtok : splits the string according to given delimiter


          while(word != NULL)                                                  //to read all the words
                {
                        if(word[0] == '>')                                             //std o/p redirection
                        {
                                if(strlen(word) > 1 && word[1] == '>')          // >> : append to the file
                                {
                                        fd = open(word+2, O_WRONLY|O_CREAT|O_APPEND|O_TRUNC, S_IRUSR|S_IRGRP|S_IWUSR|S_IWGRP);

                                        /*
                                        File mode bits :
                                             S_IRUSR : read permision, owner
                                             S_IRGRP : read permision, group
                                             S_IWUSR : write permision, owner
                                             S_IWGRP : write permision, group
                                        */
                             }
                             else                                                // > : overwrite the file
                                {
                                        fd = open(word+1, O_WRONLY|O_CREAT, S_IRUSR|S_IRGRP|S_IWUSR|S_IWGRP);
                                }
                             if(fd < 0)                                       //if having problem with opening the file
                                {
                                        perror("Problem with output redirection");
                                        exit(0);
                                }
                        }       
                        else if(word[0] == '<')                                //std i/p redirection
                        {
                                FILE *fp;
                                fp = fopen(word+1,"r");                      //r : read mode
                                if(fp == NULL)
                                {
                                        perror("Problem with input redirection");
                                        exit(0);
                                }

                                char ch;
                                fclose(fp);
                        }
                        else
                        {
                                num_of_args++;
                        }

                        word = strtok(NULL," ");                             //in order to get next token and to continue with the same
                                                                                     // string NULL is passed as first argument since strtok m$
                                                                                     //a static pointer to your previous passed string
                }

                if(num_of_args == 0)                                    //if nothing is written, and only "enter", read until "enter" 
                {
                        while((getchar())!='\n');
                        continue;
                }

                char *process[num_of_args+1];                     //to store the command and the it's arguments

                for(int i = 0 ; i < num_of_args+1 ; i++)     //allocating memory to process array
                {
                        process[i] = (char*)malloc(sizeof(char));
                }

                word = NULL;

                word = strtok(buffer," ");                        //getting the first word from buffer to identify system calls
             //printf("%i", num_of_args);
                if(num_of_args == 1 && strcmp(word, "exit") == 0)       //exit system call
                {
                        exit(0);
                }

                if(num_of_args == 1 && strcmp(word, "cls") == 0)        //clear screen system call
                {
                        system("clear");
                        while((getchar()) != '\n');                     //why ?
                        continue;
                }
                
                char helper[3] = {'.', '/', '\0'};
                strcat(helper, word);                        //to get the path of the system call code
                strcpy(process[0], helper);

                int i = 1;                                   //inedx pos fro process array
                int sz;                                      //size for array arr

                while(word)                                            //to read all the words
                {
                        word = strtok(NULL," ");                          //getting  the arguments for the command
                        if(word == NULL)
                                break;
                        else if(word[0] != '>' && word[0] != '<')               //no redirection
                        {
                                strcpy(process[i], word);
                                i++;
                        }
                        else if(word[0] == '<')                   //std i/p redirection 
                        {
                                char arr[20];
                                FILE *fd3;
                                fd3 = fopen(word+1, "r");           //r : Read only
                                if(fd3 == NULL)
                                {
                                        perror("ERROR");
                                        exit(0);
                                }

                                sz = 0;
                                char ch;

                                ch = fgetc(fd3);
                                while(ch != EOF && ch != ' ' && ch != '\n')  //read the file, word by word, and store them to process array
                                {
                                        arr[sz++] = ch;
                                        ch = fgetc(fd3);
                                }
                                while(sz > 0)
                                {
                                        arr[sz] = '\0';
                                        strcpy(process[i++], arr);
                                        sz = 0;
                                        ch = fgetc(fd3);
                                        while(ch != EOF && ch != ' ' && ch != '\n')
                                        {
                                                arr[sz++]= ch;
                                                ch = fgetc(fd3);
                                        }
                                }
                                fclose(fd3);
                        }
                }
                process[i] = NULL;                                //null termination compulsion for process array
                
                if(fd != -1)
                {
                        dup2(fd,1);
                        }
                pid_t pid;                                        //for identifying child or parent process
                pid = fork();
                if(pid == 0)                                      //child process
                {
                        int flag = execve(process[0],process,0);        //executes calls, first arg : path, 2nd : arguments for the sys call c$
                        if(flag == -1)
                        {       
                                perror("ERROR!!!!!!");
                        }
                        printf("child returned!\n");
                        command_ip[0] = '\0';   
                        exit(0);
                }
                else                                              //parent process
                {
                int status;
                        do                                           //waits untill the child process is aborted
                        {
                                wait(&status);
                        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
                        //WIFEXITED : if child process is aborted normally : returns TRUE
                        //WIFSIGNALED : if child process is aborted by signal : returns TRUE

                        while((getchar()) != '\n');
                        if(fd != -1)
                        {
                                dup2(cfd,1);                            //duplicates, fd and store it into cfd
                                close(cfd);
                                close(fd);
                        }
                }
                for(int j = 0 ; j < num_of_args+1 ; j++)          //to reuse them in next loop
                {
                        process[j] = NULL;
                }
                command_ip[0] = '\0';                                //to reuse it in next loop
                num_of_args = 0;                                     //to reuse it in next loop
        }
        return 0;
}



 
