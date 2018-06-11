#include <stdio.h>

int main (int argc, char* argv[])
{
	char a = '#';
	printf("\40\40\40\40%c\n",a);
	printf("\40\40\40%c\40%c\40\n",a,a);
	printf("\40\x20%c\x20%c\x20%c\x20\n",a,a,a);
	return 0;	
}
