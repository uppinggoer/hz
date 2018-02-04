#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

typedef struct msg_st
{
    long int msg_type;
    char text[10];
} msg_st;

int main()
{
    msg_st data;
    key_t msg_key = ftok("/tmp/msgfile", 1);

    //建立消息队列
    int msgid = msgget(msg_key, 0666 | IPC_CREAT);

    long int msgtype = 1;
#ifdef SEND
    data.msg_type = msgtype;
    memcpy(data.text, "abc", 3);
    msgsnd(msgid, (void*)&data, 10, 0);
    printf("send ok\n");
#elif RECEIVE
    msgrcv(msgid, (void*)&data, 10, msgtype, 0);
    printf("receive %s ok\n", data.text);
#endif
}