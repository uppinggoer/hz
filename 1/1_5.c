#include <stdio.h>

char c_global;

void func(){
    char c_func;
    printf("c_func %p\n", &c_func);

    getchar(); // 阻塞程序
}

int main()
{
    printf("c_global %p\n", &c_global);
    char c_main;
    printf("c_main %p\n", &c_main);
    func();
}
