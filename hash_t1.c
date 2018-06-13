/*
*哈希查找是通过计算数据元素的存储地址进行查找的一种方法
*理想情况是能够直接找到需要的记录，因此必须在记录的存储位置和其关键字之间建立一个确定的对应关系f,使每个关机中和结构中唯一的存储位置相对应
*因此在查找是只需根据这个对应的关系f找到给定值K的对应项f(K)。如结构体存在关键字和K相等的记录，则必定在f(K)的存储位置上，由此不需要进行比较便可直接
*取得所查记录。在此，称这个对应关系f为哈希函数，按这个思想建立的表为哈希表。
*哈希表不可避免冲突现象：对不同的关键字可能得到同一哈希地址，即K1不等于K2,而f(K1)=f(K2)。具有相同函数值的关键字对该哈希函数来说称为同义词。因此，在构造
*哈希表时不仅要设定一个好的哈希函数，还要设定一种处理冲突的方法。
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
/*定义查找结点元素*/
typedef struct
{
	int num;
	char name[20];
}ElemType;

/*定义哈希表*/
typedef struct
{
	ElemType *elem;
	int count;
	int size;
}HashTable;

/*定义哈希函数*/
int Hash(int num)
{
	int p;
	p=num%5;
	return p;
}

/*创建哈希表*/
void InitHash(HashTable *H)
{
	int i;
	H->elem=(ElemType*)malloc(MAX*sizeof(ElemType));
	H->count=0;
	H->size=MAX;
	for(i=0;i<MAX;i++)
		H->elem[i].num=0;
}

/*查找函数*/
int SearHash(HashTable H, int key, int *p)
{
	int c=0;
	*p=Hash(key);
	while(H.elem[*p].num!=key&&H.elem[*p].num!=0)
	{
		c=c+1;
		if(c%2==1)
			*p=*p+(c+1)*(c+1)/4;
		else
			*p=*p-(c*c)/4;
	}
	if(H.elem[*p].num==key)
		return 1;
	else
		return 0;
}

/*插入函数*/
void InsertHash(HashTable *H,ElemType e)
{
	int p;
	SearHash(*H,e.num,&p);  //获取hash值p
	H->elem[p]=e;
	++H->count;
}

int main(int argc, char* argv[])
{
	HashTable H;
	int p,key,i;
	ElemType e;
	InitHash(&H);
	for(i=0;i<3;i++)
	{
loop:	printf("请输入第%d个学生学号\n",i+1);
		scanf("%d",&e.num);
		if(!SearHash(H,e.num,&p))
		{
			printf("输入第%d个学生名字\n",i+1);
			scanf("%s",e.name);
			InsertHash(&H,e);
		}
		else
		{
			printf("该学号已经存在\n");
			goto loop;
		}	
	}	
	printf("请输入您要查找的学生学号:\n");
	scanf("%d",&key);
	if(SearHash(H,key,&p))
	{
		printf("查找成功！学生的姓名是%s\n",H.elem[p].name);
		printf("学生所在表中的位置是%d\n",p);
	}
	else
		printf("查找失败！您要查找的学生不存在！\n");
}
