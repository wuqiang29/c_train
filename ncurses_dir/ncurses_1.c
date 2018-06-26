#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main(int argc, char *argv[])
{
	initscr();
	move(5,15);

	printw("%s","hello chenghuan\n");
	refresh();
	sleep(2);
	
	endwin();
	exit(EXIT_SUCCESS);
}
