#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	FILE *in, *out;
	char ch, file1[20], file2[20];
	
	printf("Enter the file1 name:\n");
	scanf("%s",file1);
	printf("Enter the file2 name:\n");
	scanf("%s",file2);
	
	if((in = fopen(file1,"rb"))==NULL)
	{
		printf("fopen file1 failed!\n");
		exit(0);
	}

	if((out = fopen(file2,"wb"))==NULL)
	{
		printf("fopen file2 failed!\n");
		exit(0);
	}
	
	ch = fgetc(in);
	while(ch!=EOF)
	{
		fputc(ch,out);
		ch = fgetc(in);
	}
	printf("the file copy is success!\n");
	fclose(in);
	fclose(out);
	return 0;

}
