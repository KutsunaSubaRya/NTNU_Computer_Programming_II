#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define int int32_t
int readp(char str[],int buf)
{
    int i=0,deter=0;char c;
    while((c=getchar()) && c!='\n' && c!=EOF)
    {
        if(i==buf-1)
        {
            str[i++]=c;
            str[i]='\0';
            deter=1;
            break;
        }
        str[i++]=c;
    }
    if(!deter)
    {   
        str[i]='\0'; 
        if(i%2==1) 
        {
            //printf("%d\n",i);
            //printf("HI\n");
            return 2;
        }
        else if(str[i-1]=='0' && str[i-2]=='0') return 3;
        else return 1;
    }
    else
    {
        if(str[i-1]=='0' && str[i-2]=='0') return 3;
        else return 1;
    }
}
//ret(1)->accepted
//ret(2)->invalid input
//ret(3)->finish
