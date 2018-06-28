#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mysql/mysql.h>
//#include "mysql.h"
#include "app_mysql.h"

static MYSQL my_connection;
static int dbconnected = 0;
static int get_artist_id(const char *artist);

int database_start(char *name, char *pwd)
{
	if(dbconnected) return 1;
	
	mysql_init(&my_connection);

//以用户name，密码pwd，来链接本地服务器上名为blpcd的数据库	
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
int get_artist_id(const char *artist)
{
	MYSQL_RES *res_ptr;
	MYSQL_ROW mysqlrow;
	
	int res;
	char qs[250];
	char is[250];
	char es[250];
	int artist_id = -1;
	
	/*Does it already exist? */
	mysql_escape_string(es,artist,strlen(artist));	//保护artist中的特殊字符
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
				mysqlrow = mysql_fetch_row(res_ptr);
				if(mysqlrow)
				{
					sscanf(mysqlrow[0],"%d",&artist_id);
				}
			}
			mysql_free_result(res_ptr);
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

int add_tracks(struct current_tracks_st *tracks)
{
	//MYSQL_RES *res_ptr;
	char is[250];
	char es[250];
	int i, res;
	
	if(!dbconnected); return 0;
	i = 0;
	while(tracks->track[i][0])
	{
		mysql_escape_string(es,tracks->track[i],strlen(tracks->track[i]));
		sprintf(is,"INSERT INTO track(cd_id,track_id,title) VALUES(%d,%d,'%s')",tracks->cd_id,i+1,es);
		
		res = mysql_query(&my_connection,is);
		if (res) {
			fprintf(stderr,"Insert error %d: %s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
			return 0;
		}
		i++;
	}
	return 1;
}

/*增加CD*/
int add_cd(const char *artist, const char *title, const char *catalogue, int *cd_id)
{
	MYSQL_RES *res_ptr;
	MYSQL_ROW mysqlrow;
	
	int res;
	char is[250];
	char es[250];
	int artist_id = -1;
	int new_cd_id = -1;
	
	if(!dbconnected) return 0;
	
	artist_id = get_artist_id(artist);
	
	mysql_escape_string(es,title,strlen(title));	//保护cd标题中的特殊字符
	
	sprintf(is,"INSERT INTO cd(title,artist_id,catalogue) VALUES('%s','%d','%s')",es,artist_id,catalogue);
	res = mysql_query(&my_connection,is);	
	if (res) {
		fprintf(stderr,"Insert error %d: %s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		return 0;
	}
	//提前刚才插入的cd_id
	res = mysql_query(&my_connection,"SELECT LAST_INSERT_ID()");
	if (res) {
		fprintf(stderr,"SELECT error %d: %s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		return 0;
	}else {
		res_ptr = mysql_use_result(&my_connection);
		if(res_ptr)
		{
			if((mysqlrow = mysql_fetch_row(res_ptr)));
				sscanf(mysqlrow[0],"%d",&new_cd_id);
		}
		mysql_free_result(res_ptr);
	}
	
	//设置新插cd_id;
	*cd_id = new_cd_id;
	if(new_cd_id != -1) return 1;
	return 0;
}


/*通过CD_ID获取对应CD的相关描述信息*/
int get_cd(int cd_id, struct current_cd_st *dest) {
	
	MYSQL_RES *res_ptr;
	MYSQL_ROW mysqlrow;
	int res;
	char qs[250];
	
	//首先检查连接是否正常
	if(!dbconnected)
	{
		printf("database connect error\n");
		return 0;
	}
	
	memset(dest,0x00,sizeof(*dest));
	dest->artist_id = -1;
	
	sprintf(qs,"SELECT artist.id,cd.id,artist.name,cd.title,cd.catalogue FROM artist,cd WHERE artist.id = cd.artist_id and cd.id = %d",cd_id);
	
	res = mysql_query(&my_connection,qs);
	if(res){
		fprintf(stderr,"SELECT errno %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
	}
	else {
		res_ptr = mysql_store_result(&my_connection);   //使用mysql_store_result函数将所有数据一次从数据库全部取出来
		if(res_ptr)
		{
			if(mysql_num_rows(res_ptr)>0)
			{
				if(mysqlrow = mysql_fetch_row(res_ptr))
				{
					sscanf(mysqlrow[0],"%d",&dest->artist_id);
					sscanf(mysqlrow[1],"%d",&dest->cd_id);
					strcpy(dest->artist_name,mysqlrow[2]);
					strcpy(dest->title,mysqlrow[3]);
					strcpy(dest->catalogue,mysqlrow[4]);
				}
			}
			mysql_free_result(res_ptr);
		}
	}
	if(dest->artist_id == -1){
		printf("get_cd error\n");
		return 1;
	}
	return 0;
}

/*通过cd_id获取对应cd的相关曲目信息*/
int get_cd_tracks(int cd_id, struct current_tracks_st *dest)
{
	MYSQL_RES *res_ptr;
	MYSQL_ROW mysqlrow;
	
	int res;
	char qs[250];
	int i = 0,num_tracks = 0;
	
	if(!dbconnected) return 0;
	memset(dest,0x00,sizeof(*dest));
	
	dest->cd_id = -1;
	
	sprintf(qs,"SELECT track_id, title FROM track WHERE track.cd_id = %d ORDER BY track_id",cd_id);

	res = mysql_query(&my_connection,qs);
	if(res){
		
		fprintf(stderr,"SELECT errno %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
	}else {
		
		res_ptr = mysql_store_result(&my_connection);
		if(res_ptr)
		{
			if((num_tracks = mysql_num_rows(res_ptr))>0)
			{
				while(mysqlrow = mysql_fetch_row(res_ptr))
				{
					//sscanf(mysqlrow[0],"%d",dest->cd_id)
					strcpy(dest->track[i],mysqlrow[1]);
					i++;
				}
				dest->cd_id = cd_id;
			}
			mysql_free_result(res_ptr);
		}	
	}
	return num_tracks; //返回曲目个数
}

/*根据一个描述性字符串查找CD_ID*/
int find_cds(const char *search_str, struct cd_search_st *dest)
{
	MYSQL_RES *res_ptr;
	MYSQL_ROW mysqlrow;
	
	int res;
	char qs[500];
	int i = 0;
	char ss[250];
	
	int num_row;
	
	if(!dbconnected) return 0;
	memset(dest, -1, sizeof(*dest));
	mysql_escape_string(ss,search_str,strlen(search_str));
	
	sprintf(qs,"SELECT DISTINCT artist.id, cd.id FROM artist, cd WHERE artist.id = cd.artist_id AND (artist.name LIKE '%%%s%%' OR cd.title LIKE '%%%s%%%' OR cd.catalogue LIKE '%%%s%%')",ss,ss,ss);
	
	res = mysql_query(&my_connection,qs);
	if(res)
	{
		fprintf(stderr,"SELECT errno %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
	}else{	
		res_ptr = mysql_store_result(&my_connection);
		if(res_ptr)
		{
			num_row = mysql_num_rows(res_ptr);
			if(num_row>0)
			{
				while((mysqlrow = mysql_fetch_row(res_ptr)) && i<MAX_CD_RESULT)
				{
					sscanf(mysqlrow[1],"%d",&dest->cd_id[i]);
					i++;
				}				
			}
			mysql_free_result(res_ptr);
		}
	}
	return num_row;
}

/*删除CD */
int delete_cd(int cd_id)
{
	MYSQL_RES *res_ptr;
	MYSQL_ROW mysqlrow;
	
	int res, artist_id, num_row;
	char qs[255];
	
	if(!dbconnected) return 0;
	
	artist_id = -1;
	//查询cd_id对应的aritst有几张cd;
	 //这条件查询写的厉害了
	sprintf(qs,"SELECT artist_id FROM cd WHERE artist_id = (SELECT artist_id FROM cd WHERE id = '%d')", cd_id);   
	
	res = mysql_query(&my_connection,qs);
	if(res)
	{
		fprintf(stderr,"SELECT errno %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
	} else {
		res_ptr = mysql_store_result(&my_connection);
		if (res_ptr) {
			num_row = mysql_num_rows(res_ptr);
			if(num_row==1)  /*Artist not used by any other CDs*/
			{
				mysqlrow = mysql_fetch_row(res_ptr);
				sscanf(mysqlrow[0],"%d",&artist_id);
			}
			mysql_free_result(res_ptr);
		}
	}
	
	//从曲目表中删除cd_id对应的所有曲目
	sprintf(qs,"DELETE FROM track WHERE cd_id = '%d'",cd_id);
	res = mysql_query(&my_connection,qs);
	if(res)
	{		
		fprintf(stderr,"SELECT errno %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		return 0;
	}
	
	//从cd表中删除cd_id对应的专辑
	sprintf(qs,"DELETE FROM cd WHERE id = '%d'",cd_id);
	res = mysql_query(&my_connection,qs);
	if(res)
	{		
		fprintf(stderr,"SELECT errno %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		return 0;
	}
	
	if(artist_id != -1)
	{
		/*artist entry is now unrelated to any cds, then delete it*/
		sprintf(qs,"DELETE FROM artist WHERE id = '%d'",artist_id);
		res = mysql_query(&my_connection,qs);
		if(res)
		{
			fprintf(stderr,"SELECT errno %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
			return 0;
		}
	}
	return 1;
}






















