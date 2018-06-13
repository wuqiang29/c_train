#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NULLKEY 0
#define EQ(a,b) ((a)==(b))

#define success		1
#define unsuccess	0
#define duplicate	-1

typedef int status;
typedef int keytype;

int m=0;						//哈希表表长
int hashsize[]={11,19,29,37}; 	//哈希表容量递增表，一个合适的素数序列*/

typedef struct
{
	keytype key;
	int ord;
}Elemtype;
typedef struct
{
	Elemtype *elem;
	int count;
	int sizeindex;
}Hashtable;

unsigned Hash(keytype k)
{
	return k%m;
}

/*线性探测在散列*/
void collision(int *p,int d)
{
	*p=(*p+d)%m;
}

status Inithashtable(Hashtable *h)
{
	int i;
	h->count=0;
	m=hashsize[0];
	h->sizeindex=0;
	h->elem=(Elemtype *)malloc(m*sizeof(Elemtype));
	if(!(h->elem))
		exit(OVERFLOW);
	for(i=0;i<m;i++)
		h->elem[i].key=NULLKEY;
	return OK;
}

/*查找关键字k的元素*/
status Searchhash(Hashtable h,keytype k,int *p,int *c)
{
	*p=Hash(k);
	while(h.elem[*p].key!=NULLKEY&&!EQ(k,h.elem[*p].key))
	{
		(*c)++;
		if(*c<m)
			collision(p,*c);
		else
			break;
	}
	if(EQ(k,h.elem[*p].key))
		return success;
	else
		return unsuccess;
}

status Inserthash(Hashtable *h, Elemtype e)
void Recreatehashtable(Hashtable *h)
{
	int i,count=h->count;
	Elemtype *p, *elem=(Elemtype *)malloc(count*sizeof(Elemtype));
	p=elem;
	printf("重建哈希表\n");
	for(i=0;i<m;i++)
	{
		if((h->elem+i)->key!=NULLKEY)
			*p++=*(h->elem+i);
	}
	h->count=0;
	h->sizeindex++;
	m=hashsize(h->sizeindex);
	p=(Elemtype*)realloc(h->elem,m*sizeof(Elemtype));
	if(!p)
		exit(OVERFLOW);
	h->elem=p;
	for(i=0;i<m;i++)
		h->elem[i].key=NULLKEY;
	for(p=elem;p<elem+count;p++)
		Inserthash(h,*p);				
		
}
status Inserthash(Hashtable *h, Elemtype e)
{
	int c,p;
	c=0;
	if(Searchhash(*h,e.key,&p,&c))
		return duplicate
	else if(c<hashsize[(*h).sizeindex]/2)
	{
		h->elem[p]=e;
		++(h*).count;
		return OK;		
	}
	else
		Recreatehashtable(h);
	return ERROR;
}

int mian(int argc, char* argv[])
{
	Elemtype r[N]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
	Hashtable h;
	int i,p;
	status j;
	keytype k;
	Inithashtable(&h);
	for(i=0;i<N;i++)
	{
		j=Inserthash(&h,r[i]);
		if(j==duplicate)
			printf("表中已有关键字为%d的记录，无法在插入记录(%d,%d)\n",r[i].key,r[i].key,r[i].ord);		
	}
	
	
}