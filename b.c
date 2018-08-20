#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
 
int main()
{
    key_t key;
    int msgid;

    key = ftok("ple", 15);
 
    msgid = msgget(key, 0667 | IPC_CREAT);

    message.mesg_type = 4;
 
for(int i=0;i<3;i++)
{
    printf("Write message : ");

    gets(message.mesg_text);
 
    msgsnd(msgid, &message, sizeof(message), 0);

    msgrcv(msgid, &message, sizeof(message), 4, 0);
 
    printf("Message Received is : %s \n", 
                    message.mesg_text);
}
 
    msgctl(msgid, IPC_RMID, NULL);
 
    return 0;
}
