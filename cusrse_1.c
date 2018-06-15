#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main(int argc, char *argv[])
{
	initscr();			//初始化操作
	
	move(5,15);			//将光标移动到逻辑屏幕坐标(5,15)处、输出hello world，然后刷新物理屏幕的代码，最后调用sleep(2)将程序暂停两秒钟，以便在程序结束前看到输出结果
	printw("%s","Hello World");
	refresh();	
	sleep(2);
	
	endwin();			//重置操作
	exit(EXIT_SUCCESS);
}
