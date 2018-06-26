#include <stdlib.h>
#include <stdio.h>

#include <mysql/mysql.h>
//#include "mysql.h"

int main(int argc, char *argv[])
{
	MYSQL conn_ptr;
	int res;
	
	mysql_init(&conn_ptr);

	if(mysql_real_connect(&conn_ptr, "localhost", "wuqiang", "123456", "wuqiang", 0, NULL, 0))
	{
		printf("Connection success\n");		
		res = mysql_query(&conn_ptr,"INSERT INTO children(fname, age) VALUES('Sam',12)");		
		if(!res) {
			printf("Inserted %lu rows \n",(unsigned long)mysql_affected_rows(&conn_ptr));
		}else {
			fprintf(stderr,"insert error %d: %s\n",mysql_errno(&conn_ptr),mysql_error(&conn_ptr));		
		}
	//	mysql_close(&conn_ptr);	
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






//编译选项
//gcc  inset1.c -lmysqlclient -o inset1
//gcc -I/usr/include/mysql insert1.c -lmysqlclient -o insert1