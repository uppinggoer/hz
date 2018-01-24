#include <stdio.h>

struct student {
    int no;
    char name[11];
    int gender;
    char address[101];
    int math_score;
    int chinese_score;
    int english_score;
    int total_socre;
};

struct student_2 {
    char math_score;
    char chinese_score;
    char english_score;
    char total_socre;
    short gender;
    short no;
    char name[11];
    char address[101];
};

int main() {
    printf("%d, %d\n", sizeof(struct student), sizeof(struct student_2));
}