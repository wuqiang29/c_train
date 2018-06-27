#include <stdlib.h>
#include <stdio.h>

#include <mysql/mysql.h>
//#include "mysql.h"

int main(int argc, char *argv[])
{
	MYSQL conn_ptr;
	MYSQL_RES *res_ptr;
	MYSQL_ROW sqlrow;
	int res;
	
	mysql_init(&conn_ptr);

	if(mysql_real_connect(&conn_ptr, "localhost", "wuqiang", "123456", "wuqiang", 0, NULL, 0))
	{
		printf("Connection success\n");		
		res = mysql_query(&conn_ptr,"INSERT INTO children(fname, age) VALUES('Kale',7)");		
		if(!res) {
			printf("Inserted %lu rows \n",(unsigned long)mysql_affected_rows(&conn_ptr));
		}else {
			fprintf(stderr,"insert error %d: %s\n",mysql_errno(&conn_ptr),mysql_error(&conn_ptr));		
		}
	//	mysql_close(&conn_ptr);	
		res = mysql_query(&conn_ptr,"SELECT LAST_INSERT_ID()");		
		if(res) {			
			printf("SELECT error: %s\n",mysql_error(&conn_ptr));
		}else{
			res_ptr = mysql_use_result(&conn_ptr);
			if(res_ptr) {
				while ((sqlrow = mysql_fetch_row(res_ptr))) {
					printf("We inserted childno %s \n",sqlrow[0]);
				}	
				mysql_free_result(res_ptr);
			}
		}
	}
	else {
		fprintf(stderr,"Connection failed\n");
		if(mysql_errno(&conn_ptr)) {
			fprintf(stderr,"Connection error %d: %s\n",mysql_errno(&conn_ptr),mysql_error(&conn_ptr));
		}
	}
	
	mysql_close(&conn_ptr);	
	return EXIT_SUCCESS;
}


/*
插入一行后，使用LAST_INSERT_ID()函数来获取分配的ID，就像常规的SELECT语句一样。然后使用mysql_use_result()从执行的SELECT语句中获取数据并将它打印出来
*/

//编译选项
//gcc  insert2.c -lmysqlclient -o insert2
//gcc -I/usr/include/mysql insert2.c -lmysqlclient -o insert2