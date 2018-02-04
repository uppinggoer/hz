#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
 

int main(int argc, char **argv) {
    char *name = "/tmp/pipe";
    mkfifo(name, O_CREAT | O_EXCL);
    int fd;
#ifdef WRITE // gcc -D WRITE 3_14.c -o write
    fd = open(name, O_WRONLY, 0);
    write(fd, "abc", 3);
    printf("write ok \n");
#elif READ   // gcc -D READ 3_14.c -o read
    char r_buf[10];
    fd = open(name, O_RDONLY, 0);
    read(fd, r_buf, 10);
    printf("read %s ok \n", r_buf);
#endif
}

