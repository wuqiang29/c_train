#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE *fp1, *fp2;
	char fname1[50],fname2[50],ch;

	long character,space,other,digit;
	character=space=other=digit=0;

	printf("Enter test file name\n");
	scanf("%s",fname1);
	if((fp1 = fopen(fname1,"rb"))==NULL)
	{
		//printf("cannot open file\n");
		perror("can not fopen the file");
		return 0;
	}

	printf("Enter file name for write data:\n");
	scanf("%s",fname2);
	if((fp2=fopen(fname2,"wb"))==NULL)
	{
		printf("cannot fopen file\n");
		perror("cannot fopen the file");
		return 0;
	}
	
	while((ch = fgetc(fp1))!=EOF)
		if(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
			character++;
		else if(ch==' ')
			space++;
		else if(ch>='0'&&ch<='9')
			digit++;
		else
			other++;
		fclose(fp1);
		fprintf(fp2,"character:%ld space:%ld digit%ld other:%ld\n",character,space,digit,other);
		fclose(fp2);
	return 0;
}
