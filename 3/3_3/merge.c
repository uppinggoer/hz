#include <stdlib.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
    int process_num = 10;
    char *out_name_tpl = "/tmp/f_%d";
    FILE *fp_out = fopen("/tmp/order", "w");
    for (int i=0; i < process_num; i++) {
        char in_name[100];
        sprintf(in_name, out_name_tpl, i);
        FILE *fp_in = fopen(in_name, "r");

        char buf[101];
        while (fgets(buf, sizeof(buf), fp_in)) {
            fputs(buf, fp_out);
        }
        fclose(fp_in);
    }
    fclose(fp_out);
    return 0;
}

