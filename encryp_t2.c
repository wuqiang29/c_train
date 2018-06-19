#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char* sfile,char *buf,char *cfile,int k2);
int main(int argc, char* argv[])
{
	int i,k1,k2;
	char sfile[30],buf[100],cfile[30];

	printf("please input source file name\n");
	//gets(sfile);
	
	printf("please input code file name\n");
	//gets(cfile);

	printf("input the password k1\n");
	scanf("%d",&k1);
	printf("input the password k2\n");
	scanf("%d",&k2);

	srand(k1);
	for(i=0;i<k2;i++)
		buf[i]=rand()%100;
	encrypt("test_s.c",buf,"234",k2);
	return 0;
}	
void encrypt(char *sfile,char *buf,char *cfile,int k2)
{
	FILE *fp1,*fp2;
	register char ch;
	int i=0;
	
	fp1 = fopen(sfile,"rb");
	if(fp1 == NULL)
	{
		printf("can not open source fille\n");
		exit(1);
	}
	fp2 = fopen(cfile,"wb");
	if(fp2 == NULL)
	{
		printf("can not open code file\n");
		exit(1);
	}
	ch = fgetc(fp1);	
	while(!feof(fp1))
	{
		ch=ch^buf[i];
		//ch = ch^*(buf+i);	
		i++;
		if(fp2 == NULL)
		{	
			printf("fp2 is null\n");
			exit(1);
		}			
		fputc(ch,fp2);
		//printf("ch is %d\n",ch);
		//putc(ch,fp2);
		ch=fgetc(fp1);
		if(i>k2)
			i=0;	
	}
	printf("the encrypt succeed!\n");
	fclose(fp1);
	fclose(fp2);
}
