#include <stdlib.h>
#include <stdio.h>

#include <mysql/mysql.h>

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

void display_row();
void display_header();


int main(int argc, char *argv[])
{
	int res;
	int first_row = 1;
	
	mysql_init(&my_connection);
	if(mysql_real_connect(&my_connection,"localhost","wuqiang","123456","wuqiang",0,NULL,0))
	{
		printf("connect mysql success\n");		
		printf("database client version %s\n",mysql_get_client_info());
		printf("server connect info %s\n",mysql_get_host_info(&my_connection));
		printf("当前链接的服务器信息 %s\n",mysql_get_server_info(&my_connection));
		//printf("最近执行的查询信息%s\n",mysql_info(&my_connection));//通常是update insert语句
		
		res = mysql_query(&my_connection,"select childno, fname,age from children where age >12");
		if(res)
		{
			printf("select error；%s\n",mysql_error(&my_connection));
	
		} else 
		{
			//printf("最近执行的查询信息%s\n",mysql_info(&my_connection));
			//res_ptr = mysql_store_result(&my_connection);
			res_ptr = mysql_use_result(&my_connection);
			if(res_ptr)
			{
				//printf("recieved %lu rows\n",(unsigned long)mysql_num_rows(res_ptr));
				while((sqlrow = mysql_fetch_row(res_ptr)))
				{
					//printf("fetch data...\n");
					if(first_row)
					{
						display_header();
						first_row = 0;
					}
					display_row();
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
		if(sqlrow[field_count]) printf("%s ",sqlrow[field_count]);
		else printf("NULL");
		field_count++;
	}
	printf("\n");
}


void display_header()
{
	MYSQL_FIELD *field_ptr;
	
	printf("Column details:\n");
	while((field_ptr = mysql_fetch_field(res_ptr)) != NULL)
	{
		printf("\t Name: %s\n",field_ptr->name);
		printf("\t Type: ");
		if(IS_NUM(field_ptr->type)) {
			printf("Numeric field\n");
		} else {
			switch(field_ptr->type) {
				case FIELD_TYPE_VAR_STRING:
					printf("VARCHAR\n");
				break;
				case FIELD_TYPE_LONG:
					printf("LONG\n");
				break;
				
				default:
					printf("Type is %d, check in mysql_com.h",field_ptr->type);
			}
		}
		
		printf("\t Max width %ld\n",field_ptr->length);
		if(field_ptr->flags & AUTO_INCREMENT_FLAG)
			printf("\t Auto increments\n");
		printf("\n");
	}
	
}

//编译选项
//gcc  select2.c -lmysqlclient -o select2
//gcc -I/usr/include/mysql insert2.c -lmysqlclient -o insert2