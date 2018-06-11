#include<stdio.h>

int right(unsigned value,int n)
{
	unsigned z;
	z=(value >>n)|(value<<(16-n));
	return (z);
}

int left(unsigned value, int n)
{
	unsigned z;
	z = (value>>(16-n))|(value<<n);
	return z;
}
int main(int argc,char* argv[])
{
	unsigned a;
	int n;
	printf("please input a number:\n");
	scanf("%o",&a);
	printf("please  input the number of displacement:\n");
	scanf("%d",&n);
	if(n>0)
	{	
		n = -n;
		left(a,n);
		printf("the result is %o:\n",left(a,n));
	}
}
