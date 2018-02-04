#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <iostream>  
#include <signal.h>
#include <sys/sem.h>
#include <fcntl.h> 
#include <sys/wait.h> 

using namespace std;

void get_array(std::vector<int> &myvector, FILE *fp) {
    char buf[101];

    while (fgets(buf, sizeof(buf), fp)) {
        int t = atoi(buf);
        myvector.push_back(t);
    }
}

void output_array(std::vector<int> &myvector, FILE *fp_out) {
    for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it) {
        fprintf(fp_out, "%d\n", *it);
    }
}

void run(FILE *fp, char *out_name) {
    std::vector<int> myvector;

    get_array(myvector, fp);

    std::sort(myvector.begin(), myvector.end());

    FILE *fp_out = fopen(out_name, "w");
    output_array(myvector, fp_out);
    fclose(fp_out);
}


void cat_file(char *in_name, FILE *fp_out) {
    FILE *fp_in = fopen(in_name, "r");
    char buf[101];
    while (fgets(buf, sizeof(buf), fp_in)) {
        fputs(buf, fp_out);
    }
    fclose(fp_in);
}

int num_fds_ok;

void signal_hander(int signo) {
    int status;
    while (-1 != wait(&status)) {
        num_fds_ok ++;
        printf("%d\n", num_fds_ok);
    }
    signal(SIGCHLD, signal_hander);
} 

int main(int argc, char const *argv[])
{
    signal(SIGCHLD, signal_hander);

    char *in_name_tpl = "/tmp/f_r_%d";
    char *out_name_tpl = "/tmp/f_%d";
    int process_num = 10;

    for (int i=0; i < process_num; i++) {
        if (0 == fork()) {
            char in_name[100];
            sprintf(in_name, in_name_tpl, i);
            FILE *fp = fopen(in_name, "r");
            char out_tmp_name[100];
            sprintf(out_tmp_name, out_name_tpl, i);
            run(fp, out_tmp_name);
            fclose(fp);

            char out_name[100];
            sprintf(out_name, out_name_tpl, i);
            exit(0);
        }
    }

    while (num_fds_ok < process_num) {
        sleep(1);
    }

    FILE *fp_out = fopen("/tmp/order", "w");
    for (int i=0; i < process_num; i++) {
        char in_name[100];
        sprintf(in_name, out_name_tpl, i);
        cat_file(in_name, fp_out);
    }
    fclose(fp_out);
    return 0;
}





