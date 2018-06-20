#define _XOPEN_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include <gdbm-ndbm.h>
/*The above may need to be changed to gdbm-ndbm.h on some distributions*/

#include "cd_data.h"

#define CDC_FILE_BASE	"cdc_data"
#define CDT_FILE_BASE	"cdt_data"
#define CDC_FILE_DIR	"cdc_data.dir"
#define CDC_FILE_PAG	"cdc_data.pag"
#define CDT_FILE_DIR	"cdt_data.dir"
#define CDT_FILE_PAG	"cdt_data.pag"

static DBM *cdc_dbm_ptr = NULL;
static DBM *cdt_dbm_ptr = NULL;

/*打开一个或者创建一个数据库*/
int database_initialize(const int new_database)
{
	int open_mode = O_CREAT | O_RDWR;

	/* If any existing database is open then close it */
	if(cdc_dbm_ptr) dbm_close(cdc_dbm_ptr);
	if(cdt_dbm_ptr) dbm_close(cdt_dbm_ptr);
	
	if(new_database) {
		/*del the old files*/
		(void) unlink(CDC_FILE_DIR);
		(void) unlink(CDC_FILE_PAG);
		(void) unlink(CDT_FILE_DIR);
		(void) unlink(CDT_FILE_PAG);
	}
	
	/*Open some new files, creating them if required*/
	cdc_dbm_ptr = dbm_opem(CDC_FILE_BASE,open_mode,0644);
	cdt_dbm_ptr = dbm_opem(CDT_FILE_BASE,open_mode,0644);
	if(!cdc_dbm_ptr || !cdt_dbm_ptr)
	{
		fprintf(stderr,"Unable to create database\n");
		cdc_dbm_ptr = cdt_dbm_ptr = NULL;
		return 0;
	}
	return 1;
}

/*关闭已打开的数据库*/
void database_close(void)
{
	if(cdc_dbm_ptr) dbm_close(cdc_dbm_ptr);
	if(cdt_dbm_ptr) dbm_close(cdt_dbm_ptr);
	cdc_dbm_ptr = cdt_dbm_ptr = NULL;
}


/*
*传递一个指向标题项文本字符串的指针时，它将检索出一个标题项来。如果标题项没有找到，其返回数据中的标题域将为空
*/
cdc_entry get_cdc_entry(const char *cd_catalog_ptr)
{
	cdc_entry entry_to_return;
	char entry_to_find[CAT_CAT_LEN + 1];
	
	datum local_data_datum;
	datum local_key_datum;
	
	memset(&entry_to_return,'0',sizeof(entry_to_return));
		/*paragram check*/
	if(!cdc_dbm_ptr || !cdt_dbm_ptr) return entry_to_return;
	if(!cd_catalog_ptr) return entry_to_return;
	if(strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return entry_to_return;	
	
	memset(&entry_to_find,'\0',sizeof(entry_to_find));
	strcpy(entry_to_find,cd_catalog_ptr);
	
	local_key_datum.dptr = (void*)entry_to_find;
	local_key_datum.dsize = sizeof(entry_to_find);
	memset(&local_data_datum,'\0',sizeof(local_data_datum));

	local_data_datum = dbm_fetch(cdc_dbm_ptr,local_key_datum);
	if(local_data_datum.dptr) {
		memcpy(&entry_to_return,(char *)local_data_datum,local_data_datum.dsize);
	}
	return local_data_datum;
}





































