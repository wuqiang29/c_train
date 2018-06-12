#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct emploment
{
	char name[10];
	int salary;
};

struct emploment emp[20];

struct emploment emp_r[20];

int main(int argc, char* argv[])
{
	FILE *fp1, *fp2;
	int i, j, flag, n;
	char name[10], filename[20];
	
	printf("请输入文件名：\n");
	scanf("%s",filename);

	printf("请输入雇佣人的人数;\n");
	scanf("%d",&n);

	printf("请输入雇员的姓名和薪水:\n");
	for(i=0;i<n;i++)
	{
		printf("NO%d:\n",i+1);
		scanf("%s%d",emp[i].name, &emp[i].salary);
	}

	/*以追加的方式打开指定的二进制文件*/
	fp1=fopen(filename,"ab");
	if(fp1==NULL)
	{
		printf("fopen %s failed!\n",filename);
		return 0;
	}
	
	for(i=0;i<n;i++)
	{
		if(fwrite(&emp[i],sizeof(struct emploment),1,fp1)!=1)
		{
			printf("文件写入错误！\n");
			fclose(fp1);
			return 0;
		}		
	}
	fclose(fp1);
	
	/*从文件中读取员工信息*/
	fp2=fopen(filename,"rb");
	if(fp2==NULL)
	{
		printf("fopen %s failed!\n",filename);
		return 0;
	}

	for(i=0;i<n;i++)
	{
		if(fread(&emp[i],sizeof(struct emploment),1,fp2)!=1)
		{
			printf("文件读取错误！\n");
			fclose(fp2);
			return 0;
		}
	}
	fclose(fp2);

	/*输出员工信息*/
	for(i=0;i<n;i++)
	{
		printf("NO%d 姓名:%s 薪资:%d\n",i+1,emp[i].name,emp[i].salary);		
	}

	printf("\n请输入您要删除员工的姓名;\n");
	scanf("%s",name);
	
	/*从数组中查找对应员工的信息*/
	for(i=0,flag=1;i<n&&flag;i++)
	{
		if(strcmp(name,emp[i].name)==0)
		{
			for(j=i;j<n-1;j++)//此处j<n-1需要注意，防止数组越界
			{
				strcpy(emp[j].name,emp[j+1].name);
				emp[j].salary=emp[j+1].salary;
			}
			flag = 0;	
		}
	}

	if(!flag)
		n=n-1;
	else
		printf("没有找到对应员工信息！\n");
	
	/*将更新后的数组信息重新写回磁盘*/
	printf("\n更新后的员工信息\n");
	
	//为什么这个文件打开失败了
	fp1 = fopen(filename,"wb");
	
	if(fp1==NULL);
	{
		printf("fopen 之前1\n");
		printf("fopen %s failed\n",filename);
		return 0;
	}

	for(i=0;i<n;i++)
	{
		if(fwrite(&emp[i],sizeof(struct emploment),1,fp2)!=1)
		{
 			printf("fwrite 写入失败\n");
			return 0;
		}
	}
	fclose(fp1);
	
	if((fp2=fopen(filename,"rb"))==NULL)
	{
		printf("fopen 之前2\n");
		printf("fopen %s failed\n",filename);
		return 0;
	}
	for(i=0;fread(&emp[i],sizeof(struct emploment),1,fp2)!=0;i++)
		printf("\n%8s%7d",emp[i].name, emp[i].salary);/*输出员工信息*/
	printf("\n");
	fclose(fp2);
	return 1;

}
