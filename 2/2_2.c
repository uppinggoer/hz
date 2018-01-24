#include <stdio.h>
#include <string.h>

int insert(int* a, int a_len, int t) {
    for (int i=0; i< a_len; i++) {
        if (a[i] < t) {
            continue;
        } else {
            memmove(a+i+1, a+i, (a_len-i) * sizeof(int));
            a[i] = t;
            break;
        }
    }
}

int output(int*a, int a_len) {
    for (int i=0; i< a_len; i++) {
        printf("%d\n", a[i]);
    }
}

int main() {
    int a[10] = {1,3,4,6,7};
    insert(a, 5, 2);
    output(a, 6);
}