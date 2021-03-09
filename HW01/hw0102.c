#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define int int32_t
void Getline(char str[], int buf)
{
    int i=0;
    char c;
    while((c=getchar()) && c!='\n' && c!=EOF)
    {
        if(i==buf-1)
        {
            str[i++]=c;
            str[i]='\0';
            break;
        }
        str[i++]=c;
        str[i]='\0';
    }
}
int Match(char str[], char che[])
{
    for(int i=0;che[i]!='\0';i++) if(str[i]!=che[i]) return 0;
    return 1;
}
void BeforeStr(char str[], char tar[])
{
    int i=0,j;
    for(i=0;str[i]!='\0';i++)
    {
        if(str[i]==tar[0] && Match(&str[i],tar))
        {
            printf("\033[34m");
            for(j=0;tar[j]!='\0';j++) printf("%c",str[i+j]);
            printf("\033[0m");
            i+=j-1;
        }
        else printf("%c",str[i]);
    }
    printf("\n");
}
void AfterStr(char str[], char tar[], char neww[])
{
    int i=0;
    for(i=0;str[i]!='\0';i++)
    {
        int re=0;
        if(str[i]==tar[0] && Match(&str[i],tar))
        {
            printf("\033[31m");
            for(re=0;tar[re]!='\0';re++){}
            for(int j=0;neww[j]!='\0';j++) printf("%c",neww[j]);
            i+=re-1;
            printf("\033[0m");
        }
        else printf("%c",str[i]);
    }
}
signed main()
{
    char str[1050],tar[150],neww[150];
    printf("Please enter the original text:\n");
    Getline(str,1024);
    printf("Keyword:\n");
    Getline(tar,128);
    printf("New word:\n");
    Getline(neww,128);
    printf("\nBefore:\n");
    BeforeStr(str,tar);
    printf("After:\n");
    AfterStr(str,tar,neww);
    return 0;
}
