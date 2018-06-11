#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int a,i;
	FILE *file;
	char flag;
	

	if(argc<2)
	{
		printf("输入参数错误！\n");
		exit(0);
	}
	

	for(i=1;i<argc;i++)
	{
		printf("是否真的要删除文件？(y or n)\n");
		scanf("%c",&flag);
		
		if(flag=='Y'||flag=='y')
		//	remove(argv[i]);
			unlink(argv[i]);
		if(fopen(argv[i],"rb")!=NULL)
		{
			printf("删除文件失败！\n");
			exit(0);
		}
		else
		{
			printf("删除文件成功！\n");
		}		
	}
	return 0;
}
