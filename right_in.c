#include <stdio.h>
int main(int argc, char* argv[])
{
		int x=58,y=-58;
		x=x>>3;
		y=y>>3;
		printf("the result1 is: %d,%d\n",x,y);
		x=x>>2;
		y=y>>2;
		printf("the result2 is:%d,%d\n",x,y);
		return 0;

}
