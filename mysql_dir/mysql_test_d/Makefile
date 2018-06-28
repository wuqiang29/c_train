all: app

app: app_mysql.c app_mysql.h app_test.c
	gcc -o app -I/home/wuqiang/share/test_we/c_train/mysql_dir/mysql_test_d app_mysql.c app_test.c -lmysqlclient 

clean:
	rm -f *o app