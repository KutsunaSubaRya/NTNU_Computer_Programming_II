#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<ctype.h>
#include "readp.h"
int hextodec(char hex[]) 
{
    int ans=0;
    for(int i=0;i<2;i++) 
    {
        if(isdigit(hex[i])) ans=ans*16+(int)(hex[i]-'0');
        else ans=ans*16+((int)(toupper(hex[i])-'A')+10);
    }
    return ans;
}
int hextostr(char str[], char ans[]) 
{
    int j=0,cnt=0;
    size_t i=0;
    while(str[i]!='\0')
    {
        int dec=hextodec(&str[i]);
        if(dec>=32 && dec<=127) ans[j++]=dec;
        else if(dec==0) break;
        else
        {
            printf("Invalid Input\n");
            exit(0);
        }
        i+=2;
        cnt++;
    }
    return cnt;
}
signed main()
{
    char str[10001]={0},ans[10001]={0};
    char *arr=(char *)malloc(5000*sizeof(char));
    int deter=0,t=1;
    size_t fl=0;
    printf("Please enter the hex string: ");
    while((deter=readp(str,10000)))
    {
        for(int i=0;i<10001;i++) ans[i]='0';
        if(deter==2) return printf("Invalid Input\n"),0;
        else if(deter==3)
        {
            int a=hextostr(str, ans);
            //printf("%zu\n",sizeof(arr));
            for(size_t i=0;i<sizeof(char)*t*5000;i++) printf("%c",*(arr+i));
            for(int i=0;i<a;i++) printf("%c",ans[i]);
            printf("\n");
            break;
        }   
        else if(deter==1)
        {
            t++;
            hextostr(str, ans);
            for(size_t i=0+fl,j=0;i<5000+fl && j<5000;i++,j++) *(arr+i)=ans[j];
            arr=(char *)realloc(arr,sizeof(char)*5000*t);
            fl+=5000;
            //printf("%s",ans);
        }
        for(int i=0;i<10001;i++) str[i]='0';
    }
    free(arr);
    return 0;
}