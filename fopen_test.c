#include <stdio.h>
int main()
{
	FILE *f1;
	char fiename[10];
	scanf("%s",fiename);

	f1=fopen(fiename,"wb");
	if(f1==NULL)
		printf("fopen fialed\n");
	perror("fopen error");
}
