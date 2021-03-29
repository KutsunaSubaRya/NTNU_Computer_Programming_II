#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

typedef struct _sMixedNumber {
	int32_t a;
	int32_t b;
	int32_t c;
}sMixedNumber;

int _gcd_(int32_t a, int32_t b)
{
	while(b!=0){
		int tmp=a%b;
		a=b;
		b=tmp;
	}
	return a;
}

int mixed_set( sMixedNumber *pNumber , int32_t a, int32_t b, int32_t c)
{
	if(b!=c && c==0) return -1;
	if(a!=0 && (b<0 || c<0)) return -1;
	if(a==0 && (b<0 || c<0))
	{
		if(b<0 && c<0)
		{
			b=abs(b);
			c=abs(c);
		}
		else if(c<0 && b>=0)
		{
			c*=-1;
			b*=-1;
		}
	}
	if(b==c && b==0) c=1;
	pNumber->a=a;
	pNumber->b=b;
	pNumber->c=c;
	return 0;
}
	
// return -1 if invalid; otherwise , return 0.

int mixed_print( const sMixedNumber number)
{
	if(number.b==0) printf("(%d,%d,%d)\n",number.a, number.b, 0);
	else printf("(%d,%d,%d)\n",number.a, number.b, number.c);
	return 0;
}
// in the form of (a,b,c)

void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2)
{
	int r1b, r2b;
	if(r1.a>=0)
		r1b=r1.b+r1.a*r1.c;
	else
		r1b=r1.a*r1.c-r1.b;
	if(r2.a>=0)
		r2b=r2.b+r2.a*r2.c;
	else
		r2b=r2.a*r2.c-r2.b;
	int32_t gcd=_gcd_(r1.c, r2.c), lcm=(r1.c*r2.c)/gcd;
	pNumber->b=r1b*(lcm/r1.c)+r2b*(lcm/r2.c);
	pNumber->c=lcm;
	if(pNumber->b<0)
	{
		pNumber->b=abs(pNumber->b);
		pNumber->a=(pNumber->b/pNumber->c)*-1;
		pNumber->b%=pNumber->c;
		gcd=_gcd_(pNumber->b,pNumber->c);
		pNumber->b/=gcd;pNumber->c/=gcd;
	}
	else 
	{
		pNumber->a=pNumber->b/pNumber->c;
		pNumber->b%=pNumber->c;
		gcd=_gcd_(pNumber->b,pNumber->c);
		pNumber->b/=gcd;pNumber->c/=gcd;
	}
}
// pNumber = r1 + r2

void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2)
{
	int r1b, r2b;
	if(r1.a>=0)
		r1b=r1.b+r1.a*r1.c;
	else
		r1b=r1.a*r1.c-r1.b;
	if(r2.a>=0)
		r2b=r2.b+r2.a*r2.c;
	else
		r2b=r2.a*r2.c-r2.b;
	int32_t gcd=_gcd_(r1.c, r2.c), lcm=(r1.c*r2.c)/gcd;
	pNumber->b=r1b*(lcm/r1.c)-r2b*(lcm/r2.c);
	pNumber->c=lcm;
	if(pNumber->b<0)
	{
		pNumber->b=abs(pNumber->b);
		pNumber->a=(pNumber->b/pNumber->c)*-1;
		pNumber->b%=pNumber->c;
		gcd=_gcd_(pNumber->b,pNumber->c);
		pNumber->b/=gcd;pNumber->c/=gcd;
	}
	else
	{
		pNumber->a=pNumber->b/pNumber->c;
		pNumber->b%=pNumber->c;
		gcd=_gcd_(pNumber->b,pNumber->c);
		pNumber->b/=gcd;pNumber->c/=gcd;
	}
}
// pNumber = r1 - r2

void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2)
{
	int r1b, r2b;
	if(r1.a>=0)
		r1b=r1.b+r1.a*r1.c;
	else
		r1b=r1.a*r1.c-r1.b;
	if(r2.a>=0)
		r2b=r2.b+r2.a*r2.c;
	else
		r2b=r2.a*r2.c-r2.b;
	pNumber->b=r1b*r2b;
	pNumber->c=r1.c*r2.c;
	//printf("b=%d c=%d\n",pNumber->b, pNumber->c);
	int gcd=_gcd_(pNumber->b, pNumber->c);
	pNumber->b/=gcd;
	pNumber->c/=gcd;
	if(pNumber->b<0)
	{
		pNumber->b=abs(pNumber->b);
		pNumber->a=(pNumber->b/pNumber->c)*-1;
		pNumber->b%=pNumber->c;
		gcd=_gcd_(pNumber->b,pNumber->c);
		pNumber->b/=gcd;pNumber->c/=gcd;
	}
	else
	{
		pNumber->a=pNumber->b/pNumber->c;
		pNumber->b%=pNumber->c;
		gcd=_gcd_(pNumber->b,pNumber->c);
		pNumber->b/=gcd;pNumber->c/=gcd;
	}
}
// pNumber = r1 * r2

void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2)
{
	int r1b, r2b;
	if(r1.a>=0)
		r1b=r1.b+r1.a*r1.c;
	else
		r1b=r1.a*r1.c-r1.b;
	if(r2.a>=0)
		r2b=r2.b+r2.a*r2.c;
	else
		r2b=r2.a*r2.c-r2.b;
	pNumber->b=r1b*r2.c;
	pNumber->c=r1.c*r2b;
	//printf("b=%d c=%d\n",pNumber->b, pNumber->c);
	int gcd=_gcd_(pNumber->b, pNumber->c);
	pNumber->b/=gcd;
	pNumber->c/=gcd;
	if(pNumber->b<0)
	{
		pNumber->b=abs(pNumber->b);
		pNumber->a=(pNumber->b/pNumber->c)*-1;
		pNumber->b%=pNumber->c;
		gcd=_gcd_(pNumber->b,pNumber->c);
		pNumber->b/=gcd;pNumber->c/=gcd;
	}
	else
	{
		pNumber->a=pNumber->b/pNumber->c;
		pNumber->b%=pNumber->c;
		gcd=_gcd_(pNumber->b,pNumber->c);
		pNumber->b/=gcd;pNumber->c/=gcd;
	}
}
// pNumber = r1 / r2