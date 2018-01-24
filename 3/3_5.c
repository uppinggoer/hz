#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void cat_file(char *in_name, FILE *fp_out) {
    FILE *fp_in = NULL;
    while (1) {
        fp_in = fopen(in_name, "r");
        if (fp_in) {
            break;
        }

        // 还没排序完，等一秒
        sleep(1);
    }

    char buf[101];
    while (fgets(buf, sizeof(buf), fp_in)) {
        fputs(buf, fp_out);
    }
    fclose(fp_in);
}

int main(int argc, char const *argv[])
{
    int process_num = 10;
    char *out_name_tpl = "/tmp/f_%d";
    FILE *fp_out = fopen("/tmp/order", "w");
    for (int i=0; i < process_num; i++) {
        char in_name[100];
        sprintf(in_name, out_name_tpl, i);
        cat_file(in_name, fp_out);
    }
    fclose(fp_out);
    return 0;
}