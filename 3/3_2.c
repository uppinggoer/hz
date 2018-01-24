#include <stdlib.h>
#include <stdio.h>
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

int main(int argc, char const *argv[])
{
    char *out_name_tpl = "f_%d";
    int min = 0, max = 10000, process_num = 10;
    FILE *fp = fopen("/tmp/random", "r");

    for (int i=0; i < process_num; i++) {
        std::vector<int> myvector;
        int step = (max - min) / process_num;
        int start = step * i, end = step * (i + 1);

        get_array(myvector, fp, start, end);
        std::sort(myvector.begin(), myvector.end());

        char out_name[100];
        sprintf(out_name, out_name_tpl, i);
        FILE *fp_out = fopen(out_name, "w");
        output_array(myvector, fp_out);
        fclose(fp_out);
        fseek(fp, 0, SEEK_SET);
    }
    fclose(fp);

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

