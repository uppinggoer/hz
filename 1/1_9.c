#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int direction = 1;

void output(int** a, int len) {
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

void get_next(int *i, int *j) {
    if (direction == 1) {
        *i += 1;
        *j -= 1;
    } else {
        *j += 1;
        *i -= 1;
    }
}

void try_turn(int *i, int *j) {
    if (*j==0 && direction==1) {
        direction = -1;
        *i += 2; // 为了方便后续调整方向 (技巧)
        *j -= 1;
    } else if (*i==0 && direction==-1) {
        direction = 1;
        *j += 2;
        *i -= 1;
    }
}

void cal(int** a, int len) {
    int sum = len * len + 1;
    int midum = sum/2;

    int i=0,j=0;
    for (int num=1; num<=midum; num++) {
        a[i][j] = num;
        a[len-1-i][len-1-j] = sum - num;

        try_turn(&i, &j);
        get_next(&i, &j);
    }
}

int main()
{
    int** a;
    int len = 4;

    a = malloc(sizeof(int*)*len);
    for (int i=0; i<4; i++) {
        a[i] = malloc(sizeof(int) * len);
    }
    cal(a, len);
    output(a, len);
}