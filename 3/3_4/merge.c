#include <stdlib.h>
#include <stdio.h>

void cat_file(FILE *fp_in, FILE *fp_out) {
    char buf[101];
    while (fgets(buf, sizeof(buf), fp_in)) {
        fputs(buf, fp_out);
    }
    fclose(fp_in);
}

FILE* wait_open(char *in_name) {
    FILE *fp_in = NULL;
    while (1) {
        fp_in = fopen(in_name, "r");
        if (fp_in) {
            break;
        }
        // 文件不存在，还没排序完，等一秒
        sleep(1);
    }
    return fp_in;
}

int main(int argc, char const *argv[])
{
    const char* out_name_tpl = argv[1];
    int process_num = atoi(argv[2]);
    printf("%s\n", out_name_tpl);
    FILE *fp_out = fopen("/tmp/order", "w");
    for (int i=0; i < process_num; i++) {
        char in_name[100];
        sprintf(in_name, out_name_tpl, i);
        FILE* fp_in = wait_open(in_name);
        cat_file(fp_in, fp_out);
    }
    fclose(fp_out);
    return 0;
}

