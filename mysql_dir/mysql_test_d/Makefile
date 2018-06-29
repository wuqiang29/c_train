all: app

INCLUDE=/home/wuqiang/share/test_we/c_train/mysql_dir/mysql_test_d
LIBS= -lmysqlclient

app_mysql.o:app_mysql.c app_mysql.h
	@gcc -c app_mysql.c -I$(INCLUDE) $(LIBS)

app_test.o:app_test.c app_mysql.h
	@gcc -c app_test.c -I$(INCLUDE) $(LIBS)
	
app: app_mysql.o app_test.o
	@gcc -o app app_mysql.o app_test.o $(LIBS)

	
#gcc -o app -I/home/wuqiang/share/test_we/c_train/mysql_dir/mysql_test_d app_mysql.c app_test.c -lmysqlclient 

clean:
	rm -f *o app