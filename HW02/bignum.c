#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "bignum.h"
#define max(x,y) x>y?x:y

void print(const sBigNum num)
{
	if(num.sign==-1) printf("-");
	for(int32_t i=num.size-1;i>=0;i--) printf("%d",num.num[i]);
	printf("\n");
}

int32_t set(sBigNum *pNum, char *str)
{
	char *tmp=str;
	if(*tmp == '-')
	{
		pNum->sign=-1;
		tmp++; 
	}
	else pNum->sign=1;
	pNum->size=strlen(str);
	for(int32_t i=0; *tmp!='\0', i<pNum->size;tmp++, i++) pNum->num[pNum->size-1-i]=(*tmp-48);
	return 1; 
}

int32_t compare(const sBigNum num01 , const sBigNum num02)
{
	if(num01.sign==0 && num02.sign==1) return 1;
	else if(num01.sign==1 && num02.sign==0) return -1;
	else if(num01.size > num02.size) return 1;
	else if(num01.size < num02.size) return -1;
	else 
	{
		int sz=num01.size;
		for(int i=sz-1;i>=0;i--)
		{
			if(num01.num[i]>num02.num[i]) return 1;
			else if(num02.num[i]>num01.num[i]) return -1;
		}
	}
	return 0;
}

int32_t digits(const sBigNum num)
{
    return num.size;
}

void add(sBigNum *pResult ,const sBigNum num01 , const sBigNum num02) 
{
	if(num01.sign==-1 && num02.sign==1)
	{
		sBigNum *tmp = (sBigNum *)&num01;
        tmp->sign = 1;
		subtract(pResult, num02, num01);
		return;
	}
	else if(num01.sign==1 && num02.sign==-1)
	{
		sBigNum *tmp = (sBigNum *)&num02;
        tmp->sign = 1;
		subtract(pResult, num01, num02);
		return;
	}
	for(int32_t i=0;i<10005;i++) pResult->num[i]=0;
	if(num01.sign==-1 && num02.sign==-1) pResult->sign=-1;
	int tmp=0, maxu=max(num01.size, num02.size);
	for(int32_t i=0;i<maxu;i++)
	{
		pResult->num[i]+=num01.num[i];
		pResult->num[i]+=num02.num[i];
	}
	for(int32_t i=0;i<maxu;i++)
	{
		tmp=pResult->num[i]/10;
		pResult->num[i]%=10;
		pResult->num[i+1]+=tmp;
	}
	if(tmp!=0) maxu++;
	pResult->size=maxu;
}

void subtract(sBigNum *pResult, const sBigNum num01, const sBigNum num02) 
{
    if(num01.sign == 1 && num02.sign == -1) 
	{
        sBigNum *tmp = (sBigNum *)&num02;
        tmp->sign = 1;
        add(pResult, num01, num02);
        return;
    }
	else if(num01.sign == -1 && num02.sign == -1) 
	{
        sBigNum *tmp = (sBigNum *)&num01;
        tmp->sign = 1;
        tmp = (sBigNum *)&num02;
        tmp->sign = 1;
        subtract(pResult, num02, num01);
        return;
    }
	else if(num01.sign == -1 && num02.sign == 1) 
	{
        sBigNum *tmp = (sBigNum *)&num01;
        tmp->sign = 1;
        pResult->sign = -1;
        add(pResult, num02, num01);
        return;
    }
    if(compare(num01, num02) == -1) 
	{
		pResult->sign=-1;
		subtract(pResult, num02, num01);
		return;
	}
	for(int32_t i=0;i<10005;i++) pResult->num[i]=0;
    int32_t maxu = max(num01.size, num02.size);
    for(int32_t i=0; i<maxu; i++) {
        if(i < num01.size) pResult->num[i]+=num01.num[i];
        if(i < num02.size) pResult->num[i]-=num02.num[i];
    }
    for(int32_t i=0;i<maxu;i++)
    {
    	if(pResult->num[i]<0)
    	{
    		pResult->num[i]+=10;
    		pResult->num[i+1]-=1;
		}
	}
    
    if(pResult->num[maxu] < 0)  pResult->num[maxu]=-1;
    while(maxu!=1 && pResult->num[maxu-1]==0) maxu--;
    pResult->size=maxu;
    if(pResult->num[maxu-1] < 0) 
	{
		pResult->sign=-1;
		pResult->num[maxu-1]*=-1;
	}
}

void multiply( sBigNum *pResult , const sBigNum num01 , const sBigNum num02 )
{
	int32_t tmp[10005]={0},k=0;
	for(int32_t i=0;i<10005;i++) pResult->num[i]=0;
	pResult->sign=num01.sign*num02.sign;
	for(int32_t i=0;i<num01.size;i++)
	{
		for(int32_t l=0;l<10005;l++) tmp[l]=0;
		for(int32_t j=0;j<num02.size;j++)
		{
			for(int32_t l=0;l<10005;l++) tmp[l]=0;
			tmp[j]+=num01.num[i]*num02.num[j];
			tmp[j+1]+=tmp[j]/10;
			pResult->num[j+1+k]+=tmp[j+1];
			pResult->num[j+2+k]+=pResult->num[j+1+k]/10;
			pResult->num[j+1+k]%=10;
			tmp[j]%=10;
			pResult->num[j+k]+=tmp[j];
			pResult->num[j+1+k]+=pResult->num[j+k]/10;
			pResult->num[j+k]%=10;
		}
		k++;
	}
	pResult->size=num01.size+num02.size-1;
    if(pResult->num[pResult->size]!=0) pResult->size++;
    while(pResult->size!=1 && pResult->num[pResult->size-1]==0) pResult->size--;
    if(pResult->num[0] == 0 && pResult->size == 1) 
	{
		pResult->size=1;
		pResult->sign=1;
	}
}

void divide( sBigNum *pQuotient , sBigNum *pRemainder , const sBigNum num01 , const sBigNum num02 )
{
	if(compare(num01, num02)==-1)
	{
		pQuotient->size=1;
		pQuotient->num[0]=0;
		pQuotient->sign=1;
		pRemainder->size=num01.size;
		pRemainder->sign=num01.sign;
		for(int32_t i=0;i<num01.size;i++) pRemainder->num[i]=num01.num[i];
		return;
	}
	else if(compare(num01, num02)==0)
	{
		pQuotient->size=1;
		pQuotient->num[0]=1;
		pQuotient->sign=1;
		pRemainder->size=1;
		pRemainder->sign=1;
		pRemainder->num[0]=0;
		return;	
	}
	else
	{
		int32_t E=0, _sign=num01.sign * num02.sign, idx=num01.size-num02.size;
		sBigNum *cha = (sBigNum *)&num01;
	    sBigNum tmp;
	    
    	cha->sign = 1;
    	cha = (sBigNum *)&num02;
    	cha->sign = 1;
	    if(idx>0) pQuotient->size=idx+1;
	    else pQuotient->size=1;
	    for(int32_t i=0;i<10005;i++) pQuotient->num[i]=0;
	    pQuotient->sign = 1;
	    for(; idx>=0; idx--) 
		{
	        for(int i = 1; i <= 9; ++i) 
			{
	            pQuotient->num[idx] = i;
	            multiply(&tmp, *pQuotient, num02);
	            if(compare(tmp, num01) == 1) 
				{
	                pQuotient->num[idx]--;
	                break;
	            }
	            if(compare(tmp, num01) == 0) {
	                E=1;
	                break;
	            }
	            if(pQuotient->size - 1 == idx && pQuotient->num[idx] == 0) pQuotient--;
	        }
	        if(E == 1) break;
	    }
	    multiply(&tmp, *pQuotient, num02);
	    subtract(pRemainder, num01, tmp);
	    pRemainder->sign = _sign;
	    if(pQuotient->num[pQuotient->size-1] != 0) pQuotient->sign=_sign;
	    else if(pQuotient->num[pQuotient->size-1] == 0) pQuotient->size--;
	}
}

int32_t power(sBigNum *pResult, int32_t n, int32_t k)
{
	for(int32_t i=0;i<10005;i++) pResult->num[i]=0;
	int32_t te_n=n, nn=n,num01_size=0;
	if(k<0) return 0;
	if(n<0 && k&1) pResult->sign=-1;
	else pResult->sign=1;
	while(te_n>0)
	{
		te_n/=10;
		num01_size++;
	}
	sBigNum num01;
	num01.size=num01_size;
	if(nn>=0) num01.sign=1;
	else num01.sign=-1;
	for(int32_t i=0; i<num01_size; i++)
	{
		num01.num[i]=nn%10;
		nn/=10;
	}
	pResult->num[0]=1;
	pResult->sign=1;
	pResult->size=1;
	while(k>0) 
	{	
		if(k&1) multiply(pResult, *pResult, num01);
		multiply(&num01, num01, num01);
		k>>=1;
	}
	return 1;
}

int32_t combine( sBigNum *pResult, int32_t n, int32_t k )
{
	if(n<k) return 0;
	if(n<0 || k<0) return 0;
	if((n!=0 && k==0) || n==k)
	{
		pResult->num[0]=1;
		pResult->sign=1;
		pResult->size=1;
		return 1;
	}
	int32_t te_n=n, nn=n,te_k=k, kk=k, num01_size=0, num02_size=0;
	while(te_n>0)
	{
		te_n/=10;
		num01_size++;
	}
	while(te_k>0)
	{
		te_k/=10;
		num02_size++;
	}
	sBigNum num01, num02, n_k, n_fac, k_fac, n_k_fac, one, deno, p_re;
	num01.size=num01_size;
	num02.size=num02_size;
	if(nn>=0) num01.sign=1;
	else num01.sign=-1;
	for(int32_t i=0; i<num01_size; i++)
	{
		num01.num[i]=nn%10;
		nn/=10;
	}
	if(kk>=0) num02.sign=1;
	else num02.sign=-1;
	for(int32_t i=0; i<num02_size; i++)
	{
		num02.num[i]=kk%10;
		kk/=10;
	}
	
	if(compare(num01,num02)==-1) return 0;
	else if(compare(num01,num02)==0)
	{
		pResult->num[0]=1;
		pResult->sign=1;
		pResult->size=1;
		return 1;
	}
	subtract(&n_k, num01, num02);
	
	one.num[0]=1;one.sign=1;one.size=1;
	n_fac.num[0]=1;n_fac.sign=1;n_fac.size=1;
	k_fac.num[0]=1;k_fac.sign=1;k_fac.size=1;
	n_k_fac.num[0]=1;n_k_fac.sign=1;n_k_fac.size=1;
	n_k.sign=1;
	deno.num[0]=1;deno.sign=1;deno.size=1;
	//---n factor---
	while(num01.num[0]!=0 || num01.size!=1)
	{
		multiply(&n_fac, n_fac, num01);
		subtract(&num01, num01, one);
	}
	//---k factor---
	while(num02.num[0]!=0 || num02.size!=1)
	{
		multiply(&k_fac, k_fac, num02);
		subtract(&num02, num02, one);
	}
	//---n-k factor---
	while(n_k.num[0]!=0 || n_k.size!=1)
	{
		multiply(&n_k_fac, n_k_fac, n_k);
		subtract(&n_k, n_k, one);
	}
	multiply(&deno, n_k_fac, k_fac);	
	divide(pResult, &p_re, n_fac, deno);
	print(*pResult);
	return 1;
}