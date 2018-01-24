#include <stdio.h>
int main()
{
    char c;
    while(1) {
        c = getchar();
        if (c == '3') {
            printf("你输入了 3\n");
        } else if (c == '4') {
            printf("你输入大于 3\n");
        } else if (c == '5') {
            printf("这是 5\n");
        } else if (c == 'e') {
            break;
        }
    }
}
