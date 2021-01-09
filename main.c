// The Game of Life, written using ncurses

// ncurses.h includes stdio.h
#include <ncurses.h>
#include <string.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void changeYX(int ch, int* curry, int* currx);
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
	int currx = gameCol / 2;
	int curry = gameRow / 2;
	wmove(gameWindow, curry, currx); // set init cursor position to middle of gameWindow
	refresh();

	// game loop (press q to quit)
	while((ch = getch()) != 'q') {
		changeYX(ch,&curry,&currx);
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
void changeYX(int ch, int *curry, int *currx){
	switch (ch)
        {
	  // ARROW KEYS
          case KEY_LEFT:
           *currx = *currx-1;
            break;
          case KEY_RIGHT:
            *currx = *currx+1;
            break;
          case KEY_UP:
            *curry = *curry-1;
            break;
          case KEY_DOWN:
            *curry = *curry+1;
            break;

	  // VIM KEYS
          case 'h': // (left)
            *currx = *currx-1;
            break;
          case 'l': // (right)
            *currx = *currx+1;
            break;
          case 'k': // (up)
            *curry = *curry-1;
            break;
          case 'j': // (down)
            *curry = *curry+1;
            break;
	}
}
