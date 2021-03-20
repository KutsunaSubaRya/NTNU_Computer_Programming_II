#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#define int int32_t
typedef union
{
	struct {
		unsigned char b1:1;
		unsigned char b2:1;
		unsigned char b3:1;
		unsigned char b4:1;
		unsigned char b5:1;
		unsigned char b6:1;
		unsigned char b7:1;
		unsigned char b8:1;
	} bits;	
	unsigned char byte;
} uByte;
void ptuByte(uByte *num)
{
	printf("Data %d %d%d%d%d%d%d%d%d\n", num->byte, num->bits.b8, num->bits.b7, num->bits.b6, num->bits.b5, num->bits.b4, num->bits.b3, num->bits.b2, num->bits.b1);
}
signed main()
{
	uByte num;
	int deter=0;
	printf("Please enter a byte (0-255):");
	scanf("%d",&num.byte);
	ptuByte(&num);
	while(1)
	{
		printf("Flip bit (1-8, 0: exit): ");
		scanf("%d",&deter);
		if(deter>8 || deter<0) 
		{	
			printf("Invalid Input!\n");
			continue;
		}
		else if(!deter) 
		{
			return printf("Bye\n"),0;
			break;
		}
		else
		{
			if(deter==1)
			{
				num.bits.b8^=1;
				ptuByte(&num);
			}
			else if(deter==2)
			{
				num.bits.b7^=1;
				ptuByte(&num);
			}
			else if(deter==3)
			{
				num.bits.b6^=1;
				ptuByte(&num);
			}
			else if(deter==4)
			{
				num.bits.b5^=1;
				ptuByte(&num);
			}
			else if(deter==5)
			{
				num.bits.b4^=1;
				ptuByte(&num);
			}
			else if(deter==6)
			{
				num.bits.b3^=1;
				ptuByte(&num);
			}
			else if(deter==7)
			{
				num.bits.b2^=1;
				ptuByte(&num);
			}
			else if(deter==8)
			{
				num.bits.b1^=1;
				ptuByte(&num);
			}
		}
	}
}