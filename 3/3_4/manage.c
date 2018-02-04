#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

extern int errno;

int main(int argc, char const *argv[])
{
    char *out_name_tpl = "/tmp/f_%d";
    int min = 0, max = 100000, process_num = 10;
    for (int i=0; i < process_num; i++) {
        int step = (max - min) / process_num;
        int start = step * i, end = step * (i + 1);
        if (0 == fork()) {
            char out_name[100];
            sprintf(out_name, out_name_tpl, i);

            char start_s[255], end_s[255];
            sprintf(start_s, "%d", start); 
            sprintf(end_s, "%d", end); 
            execl("./hz_sort", "./hz_sort", "/tmp/random", start_s, end_s, out_name, NULL);
        }
    }

    char process_num_s[255];
    sprintf(process_num_s, "%d", process_num); 
    execl("./hz_merge", "./hz_merge", out_name_tpl, process_num_s, NULL);
    printf("errno=%d\n",errno); 
    return 0;
}

