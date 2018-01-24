#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <iostream>  

using namespace std;

void get_array(std::vector<int> &myvector, FILE *fp, int start, int end) {
    char buf[101];

    while (fgets(buf, sizeof(buf), fp)) {
        int t = atoi(buf);
        if (t < end && t >= start) {
            myvector.push_back(t);
        }
    }
}

void output_array(std::vector<int> &myvector, FILE *fp_out) {
    for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it) {
        fprintf(fp_out, "%d\n", *it);
    }
}

void run(FILE *fp, char *out_name, int start, int end) {
    std::vector<int> myvector;

    get_array(myvector, fp, start, end);

    std::sort(myvector.begin(), myvector.end());

    FILE *fp_out = fopen(out_name, "w");
    output_array(myvector, fp_out);
    sleep(2);
    fclose(fp_out);
}

int main(int argc, char const *argv[])
{
    char *out_name_tmp_tpl = "/tmp/f_%d_tmp";
    char *out_name_tpl = "/tmp/f_%d";
    int min = 0, max = 100000, process_num = 10;
    for (int i=0; i < process_num; i++) {
        int step = (max - min) / process_num;
        int start = step * i, end = step * (i + 1);
        if (0 == fork()) {
            FILE *fp = fopen("/tmp/random", "r");
            char out_tmp_name[100];
            sprintf(out_tmp_name, out_name_tmp_tpl, i);
            run(fp, out_tmp_name, start, end);
            fclose(fp);

            char out_name[100];
            sprintf(out_name, out_name_tpl, i);
            rename(out_tmp_name, out_name);
        }
    }
    return 0;
}

