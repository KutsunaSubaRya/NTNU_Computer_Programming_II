#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
signed main()
{
	double num, flo;
	int deter_num=0;
	printf("Please enter a floating -point number (double precision): ");
	scanf("%lf",&num);
	if(num>=0) printf("Sign: %d\n",0);
	else
	{
		deter_num=1;
		printf("Sign: %d\n",1);
	}
	int expo=0,inte=num,int_arr[100005]={0},deci_arr[105]={0},flag=0,cnt=1;
	flo=num-inte;
	//printf("%d,%lf\n",inte,flo);
	while(inte!=0){
 		int tmp=inte%2;
 		inte/=2;
 		int_arr[flag++]=tmp; 
 		cnt++;
	}
	if(cnt>1) cnt--;
	//printf("%d\n", cnt);
	int fl=0;
	for(int i=cnt-2;i>=0;i--) deci_arr[fl++]=int_arr[i];
	int regu_int=int_arr[cnt-1];
	//for(int j=cnt-1;j>=0;j--) printf("%d",int_arr[j]);
	while(cnt!=1)
	{
		cnt--;
		expo++;
	}
	int man_flag=expo;
	//printf("%d\n",expo);
	expo+=1023;
	int ans_expo=expo;
	int expo_cnt=0,expo_fl=0,expo_arr[100005];
	while(expo!=0){
 		int tmp=expo%2;
 		expo/=2;
 		expo_arr[expo_fl++]=tmp; 
 		expo_cnt++;
	}
	printf("Exponent: ");
	if(expo_cnt<11)
	{
		int e_cnt=11-expo_cnt;
		for(int i=0;i<e_cnt;i++) printf("0");	
	}
	for(int i=expo_cnt-1;i>=0;i--) printf("%d", expo_arr[i]);
	printf("\n");
//--------------------------------Expo finish_line--------------------------------
	printf("Fraction: ");
	for(int j=man_flag;j<52;j++){
		flo=flo*2;
		int tmp=flo;
		deci_arr[j]=tmp;
		if(tmp==1) flo=flo-tmp;
	}
	for(int j=0;j<52;j++) printf("%d",deci_arr[j]);
	printf("\n");
//--------------------------------Frac finish_line--------------------------------
	printf("%lf = (-1)^%d * (1", num, deter_num);
	for(int i=0;i<52;i++) if(deci_arr[i]==1) printf(" + 2^-%d",i+1); 
	printf(") * 2^(%d-1023)\n",ans_expo);	
	return 0;	
}