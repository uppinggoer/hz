#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <fcntl.h> 

int main(int argc, char const *argv[])
{
    int fds[2];
    pipe(fds);

    if (0 == fork()) {
        close(fds[0]);

        char tmp;
        while(gets(&tmp)){
            write(fds[1], &tmp, 1);
        }

    } else {
        close(fds[1]);

        char buf[10] = {0};
        while(read(fds[0], buf, 10)) {
            printf("read char %s\n", buf);
        }
    }
    return 0;
}


