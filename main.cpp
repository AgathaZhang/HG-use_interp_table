#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <typeinfo>

int fun(void)
{
    static int i = 0;
    i++;
    printf("num%d\n", i);
    return 0;
} 

int main()
{
    for (size_t i = 0; i < 5; i++)
    {
        fun();
        printf("num%d\n", i);
    }
    
    fun();
    printf("end coding zhang");
    return 0;
}
