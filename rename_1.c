#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>



int main(int argc, char* argv[])
{
	FILE* fp;
	char fname1[20],fname2[20];
	printf("please input the filename, which you want to change name:\n");
	scanf("%s",fname1);
	
	if(access(fname1,F_OK)!=0)              //此处可以通过两种方式检查要修改的文件是否存在，fopen只读和access F_OK
//	if((fp=fopen(fname1,"rb"))==NULL)
	{
		
		perror("can not fopen the file");
		//fprintf(stderr,"fopen file error with is :%s\n",strerror(errno));
		fprintf(stderr, "fopen error with msg is: %s\n",strerror(errno));
		return 0;
	}
	else
	{
		
		//fclose(fp);
		printf("please intput the new file name\n");
		scanf("%s",fname2);
		if(rename(fname1,fname2)==0)
			printf("rename the file %s success!\n",fname1);
		else
			printf("cannot rename the file %s!\n",fname1);	
	}
	return 0;
}
