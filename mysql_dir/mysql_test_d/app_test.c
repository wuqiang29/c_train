#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "app_mysql.h"


int main(int argc, char *argv[])
{
	struct current_cd_st cd;
	struct cd_search_st cd_res;
	struct current_tracks_st ct;
	
	int cd_id;
	int res,i;
	
	database_start("wuqiang", "123456");
	
	res = add_cd("Mahler", "Symphony No 1", "45961002", &cd_id);
	if(!res)
	{
		printf("add a cd failed \n");
		return 0;
		//printf("Result of adding a cd, cd_id is %d\n",cd_id);
	}
	printf("Result of adding a cd, cd_id is %d\n",cd_id);
	
	memset(&ct,0x00,sizeof(ct));
	
	//添加曲目信息
	cd.cd_id = cd_id;
	strcpy(ct.track[0],"Langsam Schleppend");
	strcpy(ct.track[1],"Krafting bewegt");
	strcpy(ct.track[2],"Feierlich und gemessen");
	strcpy(ct.track[3],"Sturmishch bewegt");
	add_tracks(&ct);
	
	//search cd and get the information from the getted cd
	memset(&cd_res,0x00,sizeof(cd_res));
	res = find_cds("Symphony",&cd_res);
	if(res > 0)
	{
		printf("find cd by Symphony, the cd %d\n",cd_res.cd_id[0]);
	}
	memset(&ct,0x00,sizeof(ct));
	res = get_cd_tracks(cd_res.cd_id[0],&ct);//返回指定cd的曲目个数
	
	i = 0;
	while(i<res)
	{
		printf("find track [%d] title [%s] from cd\n",i,ct.track[i]);
		i++;
	}
	
	//Delete CD for test
	res = delete_cd(cd_res.cd_id[0]);
	if(res)
	{
		printf("Delete success\n");	
		return 1;
	}
	database_end();
	return 0;
}
