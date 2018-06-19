/*
*对文本文档进行加密实质上就是读取该文档中的内容，对读出的每个字符与输入的密码进行异或，在将异或后的内容重新写入指定的磁盘文件即可
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//fgets(name, 20, stdin);//stdin 意思是键盘输入 
//fputs(name, stdout); //stdout 输出  
//char *gets(char *s);//gcc 编译器不支持gets函数，可以使用fgets进行替换，
void encrypt(char *sfile, char *pwd, char *cfile)
{
	int i=0;
	FILE *fp1,*fp2;
	register char ch;
	
	fp1 = fopen(sfile, "rb");
	if(fp1 == NULL)
	{
		printf("cannot open sourcefile.\n");
		exit(1);
	}

	fp2 = fopen(cfile, "wb");
	if(fp2 == NULL)
	{
		printf("cannot open or creat code file\n");
		exit(1);
	}

	ch = fgetc(fp1);
	while(!feof(fp1))
	{
		ch = ch^*(pwd+i);		//采用异或进行加密
		i++;
		fputc(ch,fp2);
		ch = fgetc(fp1);
		if(i>9)
			i=0;
	}
	fclose(fp1);
	fclose(fp2);
}

int main(int argc, char *argv[])
{
	char sfile[30];		//用户输入要加密的文件名
	char cfile[30];
	char pwd[10];

	printf("please input sourcefile name:\n");
	gets(sfile);
	//fgets(sfile, 30, stdin);
	
	printf("please intput password:\n");
	gets(pwd);				//可以将其理解为加密密钥
	//fgets(pwd, 10, stdin);
	
	printf("please intput codefile name:\n");	//加密后文件名
	gets(cfile);

	encrypt(sfile,pwd,cfile);
	return 0;
}
