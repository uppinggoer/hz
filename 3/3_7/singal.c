#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/sem.h>
#include <fcntl.h> 

void signal_hander(int signo) {
    printf("get signo %d\n", signo);
    exit(0);
} 

int main(int argc, char const *argv[])
{
    int pid;
    signal(SIGUSR1, signal_hander);
    if (0 == (pid = fork())) {
        while(1);
    } else {
        kill(pid, SIGUSR1);
        printf("send signo %d\n", SIGUSR1);
    }
    return 0;
}


