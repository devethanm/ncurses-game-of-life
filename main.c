// The Game of Life, written using ncurses

/* TODO
 * Make it so that the cursor appears in the gameWindow instead of on the bottom line on program star
 * Fix game windows borders (width and height) it is a little bit off, and i compensated for this in the changeYX method switch 
*/

// ncurses.h includes stdio.h
#include <ncurses.h>
#include <string.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
// not sure if maxy and x should be pointers we can optimize later
void changeYX(int ch, int* curry, int* currx, int maxy, int maxx);
void changeCell(int* y, int* x); // not sure if all methods should be declared up here im putting this here for now
// maybe we should move all game of life logic related methods to gameLogic.h and gameLogic.c or something
int main() {
	WINDOW *gameWindow;
	int startx, starty, width, height; // gameWindow properties
	char title[] = "The Game of Life";
	char instructions1[] = "Use vim or arrow keys to navigate to a cell, use enter to bring the cell to life";
	char instructions2[] = "Will update this line of instructions later";
	char exitMessage[] = "Press 'q' to quit";
	int row, col; // the stdscr window's rows and columns
	int gameRow, gameCol; // the game window's rows and columns
	int ch; // stores user char input from getch()	

	// init functions
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	// cbreak(); // line buffering disabled
	getmaxyx(stdscr, row, col); // get rows and columns of stdscr window
	// printing title and instructions to stdscr 
	mvprintw(0, (col-strlen(title))/2, "%s", title); 
	mvprintw(1, (col-strlen(instructions1))/2, "%s", instructions1); 
	mvprintw(2, (col-strlen(instructions2))/2, "%s", instructions2); 
	mvprintw(row-1, (col-strlen(exitMessage))/2, "%s", exitMessage); 
	refresh();

	// creating gameWindow and its properties
	height = LINES - 4; // subtract 4 to compensate for the 3 lines we printed above the game window
	width = COLS;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	gameWindow = create_newwin(height, width, starty, startx);
	getmaxyx(gameWindow, gameRow, gameCol); // get rows and columns of gameWindow
	int curry = gameRow / 2;
	int currx = gameCol / 2;
	wmove(gameWindow, curry, currx); // set init cursor position to middle of gameWindow
	refresh();

	// game loop (press q to quit)
	while((ch = getch()) != 'q') {
		if(ch = 'e') { // we will use e as an edit key (cycles dead or alive on cells)
			changeCell(*curry, *currx);
		}
		changeYX(ch,&curry,&currx, gameRow, gameCol);
		wmove(gameWindow, curry, currx);
		wrefresh(gameWindow);
	}
	
	endwin();
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);

	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win) {
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

// Use pointers to update current x,y
// not sure if maxy and x should be pointers we can optimize later
void changeYX(int ch, int *curry, int *currx, int maxy, int maxx) {
	switch (ch)
        {
	  // ARROW KEYS
          case KEY_LEFT:
	   if(*currx > 1) {
           	*currx = *currx-1;
	   }
            break;
          case KEY_RIGHT:
	    if(*currx < maxx - 2) {
            	*currx = *currx+1;
	    }
            break;
          case KEY_UP:
	    if(*curry > 1) {
            	*curry = *curry-1;
	    }
            break;
          case KEY_DOWN:
	    if(*curry < maxy - 2) {
            	*curry = *curry+1;
	    }
            break;

	  // VIM KEYS
          case 'h': // (left)
	    if(*currx > 1) {
            	*currx = *currx-1;
	    }
            break;
          case 'l': // (right)
	    if(*currx < maxx - 2) {
            	*currx = *currx+1;
	    }
            break;
          case 'k': // (up)
	    if(*curry > 1) {
            	*curry = *curuy-1;
	    }
            break;
          case 'j': // (down)
	    if(*curry < maxy - 2) {
            	*curry = *curry+1;
	    }
            break;
	}
}

void changeCell(int *y, int, *x) {
			
	return;
}
