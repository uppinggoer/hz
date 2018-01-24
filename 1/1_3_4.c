#include <stdio.h>
#include "1_4.h"
int main()
{
    char c;
    while(1) {
        c = getchar();
        if (c == 'e') {
            break;
        }
        output(c);
    }
}
