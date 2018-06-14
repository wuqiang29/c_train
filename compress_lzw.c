#include <stdio.h>



#define BITS	12
#define HASHSHIFT	BITS-8	//4
#define MAXVALUE	(1<<BITS)-1	//4095
#define MAXCODE	MAXVALUE-1	//4094
#define	TABLESIZE	4099

/*全局结构体变量*/
struct{
	int *code;
	int *prefix;
	char *suffix;
}lzw,*lp;


void outcode(FILE *output,int code)
{
	static int ob=0;
	static unsigned long obb=0L;
	obb|=(unsigned long)code<<(32-BITS-ob);
	ob+=BITS;
	
	while(ob>=8)
	{
		putc(obb>>24,output);		//向右移24位使低8位为要输出的数据
		obb<<=8;	
		ob-=8;	
	}
}

/*搜索哈希表的程序代码*/
int hashsearch(int prefix,int suffix)
{
	int index;
	int offset;
	
	index=(suffix<<HASHSHIFT)^prefix;
	if(index==0)
		offset=1;
	else
		offset=TABLESIZE-index;
	
	while(1)
	{
		if(lp->code[index]==-1)
			return (index);
		
		
	}
	
}