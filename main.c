#include <ncurses.h>
#include <stdio.h>
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
int main() {

	WINDOW *my_win;
	int startx, starty, width, height, colorValue;
	int ch;
	initscr();

	printw("Press F1 to exit\n");
	printw("Press up or down key");
	refresh();

	start_color();								/* Initialize Color Pairs	*/
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(1));


	cbreak();									/* Line buffering disabled	*/
	keypad(stdscr, TRUE);						/* Get F1 Key */

	height = 7;									/* Create window with box	*/
	width = 12;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	my_win = create_newwin(height, width, starty, startx);

	colorValue = 1;
	while((ch = getch()) != KEY_F(1)){	
		
		switch(ch){	

			case KEY_UP:
				colorValue++;
				break;

			case KEY_DOWN:
				colorValue--;
				break;	
		}

		if (colorValue ==8){ colorValue = 1; }
		if (colorValue ==0){ colorValue = 7; }

		wattron(my_win,COLOR_PAIR(colorValue));
		mvwprintw(my_win, height/2, 2, "Oh hello");
		wrefresh(my_win);
	}
	destroy_win(my_win);
	
	
	endwin();

	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		

	wrefresh(local_win);						/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');

	wrefresh(local_win);
	delwin(local_win);
}


/* COLOR_BLACK   0
COLOR_RED     1
COLOR_GREEN   2
COLOR_YELLOW  3
COLOR_BLUE    4
COLOR_MAGENTA 5
COLOR_CYAN    6
COLOR_WHITE   7*/
