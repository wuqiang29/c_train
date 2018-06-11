#include <stdio.h>

int main(int argc, char* argv[])
{
	int i=0, j=0, a[11][11];

	for(i=0;i<11;i++)
	{
		a[i][i]=1;
		a[i][0]=1;
	}
	
	//at third line begin

	for(i=2;i<11;i++);
	{
		for(j=1;j<=i;j++)
		{
		//	printf("the number is %d\n",a[i][j]);
			
			a[i][j]=a[i-1][j]+a[i-1][j-1];
			printf("the number is %d\n",a[i][j]);
		}	
	}

	//output the number
	for(i=0;i<11;i++)
	{
		for(j=0;j<i+1;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
			
	}

	return 0;

}
