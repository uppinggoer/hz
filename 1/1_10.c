#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[11];
    char address[101];
    int math_score;
    int chinese_score;
    int english_score;
    int total_socre;
};
    

#define offsetof(s,f) ((int)&(((s *)0)->f))
#define field_offset(o, offset, type) (*((type*)((char*)(&o) + offset)))

int main()
{
    struct student s;

    s.chinese_score = 10;

    printf("%d\n", offsetof(struct student, chinese_score));
    printf("%d\n", s.chinese_score);
    printf("%d\n", field_offset(s, offsetof(struct student, chinese_score), int));
}
