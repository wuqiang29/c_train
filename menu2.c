/*
*每当你输入一个菜单选择时，程序就调用getchar函数处理该字符，而当程序下次循环中再次调用getchar函数是，它会立刻返回一个回车符。
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
};

int getchoice(char *great, char *choices[]);

int main(int argc, char *argv[])
{
	int choice = 0;
	
	if(!isatty(fileno(stdout))) {
		
		fprintf(stderr,"You are not a terminal!\n");
		exit(1);
	}
	
	do
	{
		choice = getchoice("please select an action.",menu);
		printf("You have chosen: %c\n",choice);
	} while(choice !='q');
	exit(0);		
}

int getchoice(char *greet, char *choices[])
{
	int chosen = 0;
	int selected;
	char **option;
	
	do {
		printf("Choice:%s\n",greet);
		option = choices;
		while(*option) {
			printf("%s\n",*option);
			option++;
		}
		//忽略getchar函数返回的换行符号'\n'
		do {
				selected = getchar();
				//printf("getchar put %x\n",selected);
		} while(selected == '\n');
		//selected = getchar();
		option = choices;
		while(*option)
		{
			if(selected == *option[0]) {	//取每行首字符
				chosen = 1;
				break;
			}
			option++;
		}
		if(!chosen) {
			printf("Incorrect choice, select again\n");
		}				
	} while(!chosen);
	return selected;
}

