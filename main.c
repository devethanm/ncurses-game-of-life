// The Game of Life, written using ncurses

/* TODO
 * Make it so that the cursor appears in the gameWindow instead of on the bottom line on program start
 * Fix game windows borders (width and height) it is a little bit off, and i compensated for this in the changeYX method switch statement 
 * Fix the cursor so that after you press e to active a cell, it stays on the cell - this is a weird visual bug im not sur if its happening for you
*/

// ncurses.h includes stdio.h
#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include "gameLogic.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

MEVENT event; // for mouse events

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
	starty = (LINES - height) / 2 + 1;
	startx = (COLS - width) / 2;
	gameWindow = create_newwin(height, width, starty, startx);
	getmaxyx(gameWindow, gameRow, gameCol); // get rows and columns of gameWindow
	int curry = gameRow / 2;
	int currx = gameCol / 2;
	wmove(gameWindow, curry, currx); // set init cursor position to middle of gameWindow
	refresh();
	wrefresh(gameWindow);

	// filling gameWindow with dead cells, represented by *
	for(int i = 0; i < gameRow; i++) {
		for(int j = 0; j < gameCol; j++) {
			mvwprintw(gameWindow, i, j, "%c", '*');
		}
	}
	wrefresh(gameWindow);
	
	mousemask(ALL_MOUSE_EVENTS, NULL); // get all mouse event 

	int turns = 0;
	// game loop (press enter to begin the game)
	while((ch = getch()) != '\n') {
		changeYX(ch,&curry,&currx, gameRow, gameCol);
		wmove(gameWindow, curry, currx);
		wrefresh(gameWindow);

		if (ch == 'e' || ch == KEY_MOUSE) {
			if(((winch(gameWindow) & A_CHARTEXT) == '*')) {
				wprintw(gameWindow,"%c",'@');
			}
			else {
				wprintw(gameWindow,"%c",'*');
			}
			wrefresh(gameWindow);
		}

		// press q to exit program
		if (ch == 'q'){								// Stops user input if enter is pressed.
			endwin();
			printf("program aborted before game start \n");
			return 0;								// (if wanted we can change this)
		}
	}

	turns = runGame(gameWindow, gameRow, gameCol); 	// This will "run" the game it will, update the gameWindow based on gameLogic.
	endwin();
	printf("total turns = %d \n", turns);
	printf("program aborted \n");
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
