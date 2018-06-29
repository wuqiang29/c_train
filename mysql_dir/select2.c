#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mysql/mysql.h>

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

void display_row();

int main(int argc, char *argv[])
{
	int res;
	int id,age;
	char name[30];
	
	mysql_init(&my_connection);
	if(mysql_real_connect(&my_connection,"localhost","wuqiang","nE7jA%5m","wuqiang",0,NULL,0))
	{
		printf("connect mysql success\n");
		
		res = mysql_query(&my_connection,"select childno, fname,age from children where age >12");
		if(res)
		{
			printf("select error；%s\n",mysql_error(&my_connection));
	
		} else 
		{
			//res_ptr = mysql_store_result(&my_connection);
			res_ptr = mysql_use_result(&my_connection);
			if(res_ptr)
			{
				//printf("recieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
				while((sqlrow = mysql_fetch_row(res_ptr)))
				{
					sscanf(sqlrow[0],"%d",&id);
					strcpy(name,sqlrow[1]);
					sscanf(sqlrow[2],"%d",&age);	
					printf("fetch data id [%d] age [%d] name [%s]...\n",id,age,name);
					//通过循环取出所有数据组
					//display_row();
				}
				if(mysql_errno(&my_connection))
				{
					fprintf(stderr,"retrieve error: %s\n",mysql_error(&my_connection));
				}
			}
			mysql_free_result(res_ptr);
		}
		mysql_close(&my_connection);
	}else 
	{
		
		fprintf(stderr,"Connection failed\n");
		if(mysql_errno(&my_connection))
		{
			fprintf(stderr,"Connection error %d: %s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		}
	}
	
	return EXIT_SUCCESS;
}

void display_row()
{
	unsigned int field_count = 0;
	
	while(field_count < mysql_field_count(&my_connection))
	{
		//取出一组数据，通过循环将该组数据中编号，姓名，年龄全部打印出来
		printf("%s ",sqlrow[field_count]);
		field_count++;
	}
	printf("\n");
}

//编译选项
//gcc  select2.c -lmysqlclient -o select2
//gcc -I/usr/include/mysql insert2.c -lmysqlclient -o insert2