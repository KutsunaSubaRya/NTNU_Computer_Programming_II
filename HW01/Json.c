#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define int int32_t
int Json(const char str[], char que[], char *ans){
    char *par = strtok(que, ".");
    const char *flag=str;
    int brac=0,pbrac=0,deter=0;
    while(par!=NULL && *flag!='\0'){
        ++pbrac;
        for(;*flag != '\0'; flag++){
            if(*flag == '{') brac++; else if (*flag == ',') deter = 0; else if (*flag == ':') deter=1; else if (*flag == '}') brac--;
            else if (*flag=='"' && pbrac==brac && deter==0) {
                flag++;
                int i,j;
                for(i=0, j=0; par[j]!=0;++i, ++j) if(flag[i]!=par[j]) break;
                if(par[j]=='\0' && flag[i]=='"' && (flag[i+1]==' ' || flag[i+1]==':')) break;
                flag+=i;
            }
        }
        if(*flag!='\0'){
            deter=0;
            flag=strchr(flag, ':');
            flag++;
        }
        par=strtok(NULL, ".");
	}
    if(*flag == '\0') return 0;
    else{
        int deter=0,i=0;
        while(*flag==' ' || *flag=='"') {
            if(*flag == '"') deter=1;
            flag++;
        }
        if(deter == 1) for(;*flag != '"';flag++,i++) ans[i] = *flag;
        else if(deter == 0) for(;*flag!=' ' && *flag!='}' && *flag!=','; flag++, i++) ans[i] = *flag;
        ans[i] = '\0';
        return 1;
    }
}