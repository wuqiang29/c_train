#define _XOPEN_SOURCE


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "cd_data.h"

#define TMP_STRING_LEN	125

typedef enum {
	mo_invalid,
	mo_add_cat,
	mo_add_tracks,
	mo_del_cat,
	mo_find_cat,
	mo_list_cat_tracks,
	mo_del_tracks,
	mo_count_entries,
	mo_exit
}menu_options;

static  void announce(void)
{
	printf("\nWelcome to the demonstration CD catalog database program\n");
}

static menu_options show_menu(const cdc_entry *cdc_selected)
{
	char tmp_str[TMP_STRING_LEN + 1];
	menu_options option_chosen = mo_invalid;
	
	while (option_chosen == mo_invalid) {
		if(cdc_selected->catalog[0]) {
			printf("\n\nCurrent entry: ");
			printf("%s, %s, %s, %s\n", cdc_selected->catalog,
			cdc_selected->title,
			cdc_selected->type,
			cdc_selected->artist);
			
			printf("\n");
			printf("1-add new CD\n");
			printf("2-search for a CD\n");
			printf("3-count the CDs and tracks int the database\n");
			printf("4-re-enter tracks for current CD\n");
			printf("5-delete this CD, and all its tracks\n");
			printf("6-list tracks for this CD\n");
			printf("q-quit\n");
			printf("\nOption:\n");
			fgets(tmp_str,TMP_STRING_LEN,stdin);
			
			switch(tmp_str[0]) {
				case '1':option_chosen = mo_add_cat;break;			
				case '2':option_chosen = mo_find_cat;break;
				case '3':option_chosen = mo_count_entries;break;
				case 'q':option_chosen = mo_exit;break;
			}
		}
	}
	return option_chosen;
}

static int get_confirm(const char* question)
{
	char tmp_str[TMP_STRING_LEN + 1];
	printf("%s",question);
	
	fgets(tmp_str,TMP_STRING_LEN,stdin);
	if(tmp_str[0] == 'Y' || tmp_str[0] == 'y') {
		return 1;
	}
	return 0;	
}

/*
*让用户输入一个新的标题项
*/
static int enter_new_cat_entry(cdc_entry *enter_to_update)
{
	cdc_entry new_entry;
	
}



























