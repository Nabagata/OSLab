#include<stdio.h>
#include<sys/types.h>
#include<signal.h>

int main(int argc,char* argv[])
{
    if (argc < 2)
    {
        printf("usage: ./kill PID");
        return -1;
    }

    kill(atoi(argv[1]), SIGKILL);
    return 0;
}

