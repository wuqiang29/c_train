#include <stdlib.h>
#include <stdio.h>

#include <mysql/mysql.h>
//#include "mysql.h"

int main(int argc, char *argv[])
{
	MYSQL conn_ptr;
	mysql_init(&conn_ptr);
	if(mysql_real_connect(&conn_ptr, "localhost", "rick", "123456", "wuqiang", 0, NULL, 0)){ //错误的用户名
		printf("Connection success\n");
	//	mysql_close(&conn_ptr);
	} else {
		//printf("Connection failed\n");
		fprintf(stderr,"Connection failed\n");
		if(mysql_errno(&conn_ptr)) {
			fprintf(stderr,"Connection error %d:%s\n",mysql_errno(&conn_ptr),mysql_error(&conn_ptr));
		}
	}
	
	mysql_close(&conn_ptr);
	return EXIT_SUCCESS;
}


//编译选项
//gcc  connect1.c -lmysqlclient -o connect1
//gcc -I/usr/include/mysql connect1.c -lmysqlclient -o connect1
