#include <stdio.h>
#include <string.h>

int queues_len = 10;
int a[20];

int init_queue()
{
    int idx = 0;
    while (idx < queues_len) {
        a[idx] = idx + 1;
        idx += 1;
    }
}

int t() {
    int idx = 0;
    while (idx < queues_len) {
        printf("%d\n", a[idx]);
        idx += 1;
    }
}

int queue(int num)
{
    int tmp = a[0];
    printf("%d say %d\n", a[0], num);
    // 重新排队
    memmove(a, a+1, (queues_len-1) * sizeof(int));

    a[queues_len-1] = tmp;
}
int is_de_queue(int num)
{
    return num % 3 == 0;
}
void de_queue(int num)
{
    queues_len -= 1;
}
int is_only_one()
{
    return queues_len == 1;
}

int main()
{
    init_queue();

    int num = 1;
    while (1) {
        queue(num);
        if (is_de_queue(num)) {
            de_queue(num);
        }
        if (is_only_one()) {
            break; // 停止报数
        }
        
        num += 1;
        
    }
    printf("last people %d\n", a[0]);
    return 0;
}