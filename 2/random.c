#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>  

int main() 
{  
	for(int i = 0; i < 10000000;i++ )  
        printf("%d\n", rand()%1000000);  
}
