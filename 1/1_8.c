#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue {
    int queues_len;
    int *a;
};

int init_queue(struct queue *q, int len)
{
    q->a = malloc(len * sizeof(int));
    q->queues_len = len;

    int idx = 0;
    while (idx < q->queues_len) {
        q->a[idx] = idx + 1;
        idx += 1;
    }
}

int queue(struct queue *q, int num)
{
    int tmp = q->a[0];
    printf("%d say %d\n", q->a[0], num);
    // 重新排队
    memmove(q->a, q->a+1, (q->queues_len-1) * sizeof(int));

    q->a[q->queues_len-1] = tmp;
}
int is_de_queue(int num)
{
    return num % 3 == 0;
}
void de_queue(struct queue *q, int num)
{
    q->queues_len -= 1;
}
int is_only_one(struct queue *q)
{
    return q->queues_len == 1;
}

int main()
{
    struct queue q;
    init_queue(&q, 10);

    int num = 1;
    while (1) {
        queue(&q, num);
        if (is_de_queue(num)) {
            de_queue(&q, num);
        }
        if (is_only_one(&q)) {
            break; // 停止报数
        }
        
        num += 1;
        
    }
    printf("last people %d\n", q.a[0]);
    return 0;
}