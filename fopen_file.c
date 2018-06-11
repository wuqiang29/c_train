#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	FILE *h=NULL;
	char filename[16];
LOOP:	printf("请输入要创建的文件名！\n");
	scanf("%s",filename);
	if((h=fopen(filename,"a+"))==NULL)
	{
		printf("文件创建失败!\n");
		goto LOOP;	
	}
	else
	{
		printf("文件创建成功!\n");
	}
	return 0;

}
