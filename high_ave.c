#include <stdio.h>
void main()
{
	float a1=0,a2=0,a3=0;
	float avg=0;
	printf("输入3个学生的身高：（单位：CM）\n");
	scanf("%f%f%f",&a1,&a2,&a3);
	avg=(a1+a2+a3)/3;
	printf("平均身高为：%f\n",avg);
	
}
