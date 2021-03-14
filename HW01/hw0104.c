#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "Json.h"
#define int int32_t
signed main(){
	char I_str[3000]={0},que[3000]={0};
	char *ans; ans=(char *)malloc(40000);
	int n;
    printf("Please enter the json string:\n");
	if(fgets(I_str, 2049, stdin)){};
	while(1){
		printf("Choice (0:Exit ,1:Get) : ");
		if(scanf("%d",&n)){};
		setbuf(stdin, NULL);
		if(n==1){
			printf("Key: ");
			if(fgets(que, 2049, stdin)){};
			char *fl=que;
			for(; *fl!='\n'; *fl++);
			*fl='\0';
			int deter=Json(I_str, que, ans);
			if(deter) printf("Value: %s\n",ans);
			else printf("Cannot find what you search for~\n");
		}
		else if(n==0){
			printf("Bye\n");
			break;
		}
		else printf("Invalid Input!\n");
	}
	return 0;
}