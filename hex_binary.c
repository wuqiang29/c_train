#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int i=0, j=0, number=0, n=0;
	int a[16]={0};

	system("clear");
input_lab:	printf("please input a decimal number(0~32767):\n");
	scanf("%d",&number);
	if(number<0||number>32767)
	{
		printf("input number is invalid,please resum load\n");
		goto input_lab;
	}	


	for(i=0;i<16;i++)
	{
		n=number%2;
		j=number/2;
		number = j;
		a[i]=n;
	}
	
	//output binary number, form high to low
	for(i=15;i>=0;i--)
	{
		printf("%d",a[i]);
		if(i%4==0)
			printf(" ");
	}
	printf("\n");
	return 0;
}
