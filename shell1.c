#define _APUE_H
#define _XOPEN_SOURCE 600 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/termios.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif
/* some systems still require this */
/* for winsize */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#define MAXLINE 4096

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH) typedef voi$
#define min(a,b)     ((a) < (b) ? (a) : (b))
#define max(a,b)     ((a) > (b) ? (a) : (b))

#include <sys/wait.h>
int main(void)
{
    char    buf[MAXLINE];
    pid_t   pid;
    int     status;
    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;
        if ((pid = fork()) < 0) {
            printf("fork error");
        } else if (pid == 0) { /* child */ execlp(buf, buf, (char *)0); exit(127);
    }
        if ((pid = waitpid(pid, &status, 0)) < 0)
            printf("waitpid error");
        printf("%% ");
}
exit(0); }



