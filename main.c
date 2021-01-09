// The Game of Life, written using ncurses

// ncurses.h includes stdio.h
#include <ncurses.h>
#include <string.h>

WINDOW *createGameWindow(int height, int width, int starty, int startx);
void destroyWin(WINDOW *localWin);

int main() {
	char title[] = "The Game of Life";
	char instructions1[] = "Use vim or arrow keys to navigate to a cell, use enter to bring the cell to life";
	char instructions2[] = "Will add this line of instructions later";
	char exitMessage[] = "Press 'q' to quit";
	int row, col; // the ncurses window's rows and columns
	int ch; // stores user char input from getch()	

	// init functions
	initscr();
	noecho();
	// cbreak(); // line buffering disabled
	getmaxyx(stdscr, row, col); // get rows and columns of stdscr window
	
	//printing title and instructions at the top of stdscr
	mvprintw(0, (col-strlen(title))/2, "%s", title); 
	mvprintw(1, (col-strlen(instructions1))/2, "%s", instructions1); 
	mvprintw(2, (col-strlen(instructions2))/2, "%s", instructions2); 
	mvprintw(row-1, (col-strlen(exitMessage))/2, "%s", exitMessage); 
	refresh();

	
	while((ch = getch()) != 'q') {

	}
	endwin();
	return 0;
}

