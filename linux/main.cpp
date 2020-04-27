#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 512

struct message
{
    long msg_type;
    char msg_text[BUFFER_SIZE];
};
int main()
{
    int qid;
    struct message msg;

    /*������Ϣ����*/
    if ((qid = msgget((key_t)1234, IPC_CREAT | 0666)) == -1)
    {
        perror("msgget");
        exit(1);
    }

    printf("Open queue %d\n", qid);

    while (1)
    {
        printf("Enter some message to the queue:");
        if ((fgets(msg.msg_text, BUFFER_SIZE, stdin)) == NULL)
        {
            puts("no message");
            exit(1);
        }

        msg.msg_type = getpid();

        /*�����Ϣ����Ϣ����*/
        if ((msgsnd(qid, &msg, strlen(msg.msg_text), 0)) < 0)
        {
            perror("message posted");
            exit(1);
        }

        if (strncmp(msg.msg_text, "quit", 4) == 0)
        {
            break;
        }
    }

    exit(0);
}