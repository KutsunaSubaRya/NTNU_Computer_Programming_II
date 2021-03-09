#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "hw0103.h"
#define int int32_t
void Swap(char **x, char **y)
{
    char *temp=*x;
    *x=*y;
    *y=temp;
}
signed main()
{
    Swap(&pStr01, &pStr02);
    print_answers();
    return 0;
}
