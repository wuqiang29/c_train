#include <stdio.h>
int main()
{
	float i,h=100,s=100;
	for(i=1;i<=10;i++)
	{
		h=h/2;
		s+=h*2;
		printf("第%f次落地高度%f\n",i,h);
	}
	printf("十次落地总长度是:\40%f\n",s-h);
	printf("第十次落地后弹起的高度:\40%f",h);
	printf("\n");
}
