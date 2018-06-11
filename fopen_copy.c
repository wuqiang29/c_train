#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define bsize 1024

int main(int argc, char* argv[])
{
	FILE *f1=NULL, *f2=NULL;
	int i=0, b=0;
	char buf[bsize]={0};

	if(argc<3)
	{
		printf("input program invalid!\n");
		exit(1);
	}
	
	f1=fopen(argv[argc-1],"wb");
	if(f1==NULL)
	{
		printf("创建文件%s失败！\n",argv[argc-1]);
		exit(1);
	}

	for(i=1;i<argc;i++)
	{
		if((f2=fopen(argv[i],"rb"))==NULL)
		{	
			printf("打开文件%s失败！\n",argv[i]);
			exit(1);
		}
		while((b=fread(buf,sizeof(char),bsize,f2))>0)
		{
			fwrite(buf,sizeof(char),bsize,f1);
			printf("数据复制成功！\n");
		}

		fclose(f2);
	}
	fclose(f1);
}
