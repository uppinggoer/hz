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

int main(int argc, char const *argv[])
{
    const char* file_name = argv[1];
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);
    const char* out_name = argv[4];

    FILE *fp = fopen(file_name, "r");
    std::vector<int> myvector;
    get_array(myvector, fp, start, end);
    std::sort(myvector.begin(), myvector.end());

    char out_tmp_name[100];
    sprintf(out_tmp_name, "%s_%s", out_name, "t");
    FILE *fp_out = fopen(out_tmp_name, "w");
    output_array(myvector, fp_out);

    rename(out_tmp_name, out_name);

    fclose(fp_out);
    fclose(fp);
    return 0;
}

