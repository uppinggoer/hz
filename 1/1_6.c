#include <stdio.h>

int func(int n){
    int res = 1;
    while (n > 1) {
        res *= n;
        n -= 1;
    }
    return res;
}

int main()
{
    int N = 0;
    scanf("%d", &N);

    int res = 0;
    while (N > 0) {
        res += func(N);
        N -= 1;
    }

    printf("%d\n", res);
}
