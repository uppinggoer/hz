#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>  

int main() 
{  
	for(int i = 0; i < 100000000;i++ )  
        printf("%d\n", rand()%100000);  
}
