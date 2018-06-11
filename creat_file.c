#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//以只写方式打开一个文件，如果原文件存在，则将此文件截断为零

int main(int argc, char* argv[])
{
	int ret=0;
	char file_name[16];
LOOP:	printf("please intpute the file name:\n");
	scanf("%s",file_name);
	
	if((ret=creat(file_name,S_IRUSR|S_IWUSR))==-1)
	{
		printf("文件已存在或者路径错误\n");
		goto LOOP;	
	}
	else 
	{
		printf("文件创建成功。\n");
		close(ret);
	}	
	return 0;
}
