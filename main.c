#include <ncurses.h>
#include <stdio.h>

int main() {
	int ch;

	// init functions
	initscr();
	raw();
	noecho();

	printw("type any character, press q to quit\n");
	while( ch != 'q') {	
		ch = getch();
	
		addch(ch);
		refresh();
	}
		
	// These last two lines are just a way to keep the program open,
	// so it doesnt disapear instantly after running
	// getch();
	endwin();

	return 0;
}

