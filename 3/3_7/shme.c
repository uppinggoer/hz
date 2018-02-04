#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/shm.h>

int main()
{
    key_t mem_key = ftok("/tmp/shmekey", 1);

    //建立消息队列
    int mem_id = shmget(mem_key, sizeof(int), IPC_CREAT|0660);
    void* shm = shmat(mem_id, 0, 0);

#ifdef WRITE1
    memcpy(shm, "1", 1);
    sleep(2);
    printf("write %s ok\n", shm);
    sleep(5);
    shmdt(shm);
#elif WRITE2
    memcpy(shm, "2", 1);
    sleep(5);
    printf("write %s ok\n", shm);
    sleep(5);
    shmdt(shm);
#elif READ
    printf("read %s ok\n", (char*)shm);
    shmdt(shm);
    shmctl(mem_id , IPC_RMID , NULL);
#endif
}