#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	const char witch_one[] = " First Witch ";
	const char witch_two[] = " Second Witch ";
	const char *scan_ptr;

	initscr();

	move(5,15);
	attron(A_BOLD);
	printw("%s","Macbeth");
	attroff(A_BOLD);
	refresh();
	sleep(1);

	move(8,15);
	attron(A_STANDOUT);
	printw("%s","Thunder and Lightning");
	attroff(A_STANDOUT);
	refresh();
	sleep(1);

	move(10,10);
	printw("%s","When shall we three meet again");
	move(11,23);
	printw("%s","In thunder, lightning, or in train ?");
	attroff(A_STANDOUT);
	refresh();
	sleep(1);

	attron(A_DIM);
	scan_ptr = witch_two + strlen(witch_two) - 1;
	//while(scan_ptr != witch_two) {
	//	move(13,10);
	//	insch(*scan_ptr--);
	//}
	
	move(13,10);
	
	printw("%s",witch_two);	
	
	attroff(A_DIM);
	refresh();
	sleep(1);

	move(LINES - 1, COLS - 1);
	
	refresh();
	sleep(10);
	//while(1)
	//{}
	
	endwin();
	exit(EXIT_SUCCESS);
}
