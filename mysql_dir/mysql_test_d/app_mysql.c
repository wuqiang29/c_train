#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mysql.h"
#include "app_mysql.h"

static MYSQL my_connection;
static int dbconnected = 0;
static int get_artist_id(char *artist);

int database_start(char *name, char *pwd)
{
	if(dbconnected) return 1;
	
	mysql_init(&my_connection);
	
	if(mysql_real_connect(&my_connection,"localhost",name,pwd,"blpcd",0,NULL,0)){
		printf("Connection success\n");
	} else {
		fprintf(stderr,"Connection error %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		return 0;
	}
	dbconnected = 1;
	return 1;
}

void database_end()
{
	if(dbconnected) mysql_close(&my_connection);
	dbconnected = 0;
}

/*Find or create an artist_id for the given string */
static int get_artist_id(char *artist)
{
	MYSQL_RES *res_ptr;
	MYSQL_ROW *mysqlrow;
	
	int res;
	char qs[250];
	char is[250];
	char es[250];
	int artist_id = -1;
	
	/*Does it already exist? */
	mysql_escape_string(es,artist,strlen(artist));
	sprintf(qs,"SELECT id FROM artist WHERE name = '%s'",es);
	
	res = mysql_query(&my_connection,qs);
	if(res)
	{
		fprintf(stderr,"SELECT errno %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		
	} else {
		res_ptr = mysql_store_result(&my_connection);
		if(res_ptr)
		{
			if(mysql_num_rows(res_ptr) > 0) {
				if(mysqlrow = mysql_fetch_row(res_ptr))
				{
					sscanf(mysqlrow[0],"%d",&artist_id);
				}
			}
			mysql_free_result(&my_connection);
		}
	}
	
	if(artist_id != -1) return artist_id;
	
	sprintf(is,"INSERT INTO artist(name) VALUE('%s')",es);
	res = mysql_query(&my_connection,is);
	if(res) {
		fprintf(stderr,"Insert error %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		return 0;
	}
	res = mysql_query(&my_connection,"SELECT LAST_INSERT_ID()");
	
	if(res) {
		
		printf("SELECT error:%s\n",mysql_error(&my_connection));
		return 0;
	}else {
		
		res_ptr = mysql_use_result(&my_connection);
		if(res_ptr) {
			if((mysqlrow = mysql_fetch_row(res_ptr))) {
				sscanf(mysqlrow[0],"%d", &artist_id);
			}
			mysql_free_result(res_ptr);
		}
	}
		
	return artist_id;		
}

int add_trackes(struct current_tracks_st *tracks)
{
	//MYSQL_RES *res_ptr;
	char is[250];
	char es[250];
	int i;
	
	if(!dbconnected); return 0;
	i = 0;
	while(tracks->track[i][0])
	{
		
		
		
	}
	
	sprintf(qs,"INSERT INTO ")
	
}