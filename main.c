// The Game of Life, written using ncurses 
/* TODO
 * Add 'c' to clear or something to reset the board
 * add board presents like many game of life websites have
*/


#include <ncurses.h>
#include <menu.h> // menu library for ncurses
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gameLogic.h"
#include "cell.h"

struct Cell* head = NULL;
struct Cell* tail = NULL;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void setupScreen();
char *my_itoa(int i);
MEVENT event; // for mouse events

char *choices[] = {
			"Save Preset",
			"Clear Board",
			"Exit",
		};

int main() {
	WINDOW *gameWindow;
	int startx, starty, width, height; // gameWindow properties
	int gameRow, gameCol; // the game window's rows and columns
	int ch; // stores user char input from getch()
	int curry, currx; // keeps track of current position on screen

	// init functions
	initscr();
	cbreak();
	keypad(stdscr, TRUE);      
	noecho();
	start_color();					/* Initialize Color Pairs	*/
	build_color_pairs();

	// MENU DECLARATIONS
	ITEM **items;
	MENU *menu;
	int numChoices;
	ITEM *curItem;
	
	//MENU SETUP
	numChoices = (sizeof(choices) / sizeof(choices[0]));
	items = (ITEM**)calloc(numChoices+1, sizeof(ITEM *));

	for(int i = 0; i < numChoices; i++) 
		items[i] = new_item(my_itoa(i+1), choices[i]);
	
	items[numChoices] = (ITEM *)NULL;
	menu = new_menu((ITEM**) items);
	post_menu(menu);
	refresh();
	int menuChoice = -1;

	while((ch = getch()) != KEY_F(1))
	{   switch(ch)
	    {	case KEY_DOWN:
		        menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
			case '\n': // Enter
				menuChoice = item_index(current_item(menu));  // can use curry to see what choice is
				break;
		}

		if (menuChoice != -1){break;}
	}
	unpost_menu(menu);
	if(menuChoice == 2){
		endwin();
		return 0;
	}
	// PRINT INSTRUCTIONS
	setupScreen();

	// creating gameWindow & properties
	height = LINES - 4; // subtract 4 to compensate for the 3 lines we printed above the game window
	width = COLS - 2;
	starty = (LINES - height) / 2 + 1;
	startx = (COLS - width) / 2;
	gameWindow = create_newwin(height, width, starty, startx);
	getmaxyx(gameWindow, gameRow, gameCol); // get rows and columns of gameWindow

	// filling gameWindow with dead cells
	for(int i = 0; i < gameRow; i++) {
		for(int j = 0; j < gameCol; j++) {
			mvwprintw(gameWindow, i, j, "%c", deadChar);
		}
	}

	curry = gameRow / 2;
	currx = gameCol / 2;
	wmove(gameWindow, curry, currx); // set init cursor position to middle of gameWindow
	wrefresh(gameWindow);
	
	mousemask(ALL_MOUSE_EVENTS, NULL); // get all mouse event 

	int turns = 0;
	// game loop (press enter to begin the game)
	while((ch = getch()) != '\n') {
		changeYX(ch,&curry,&currx, gameRow, gameCol);
		wmove(gameWindow, curry, currx);
		wrefresh(gameWindow);
		struct Cell* temp;
		
		if (ch == 'e' || ch == KEY_MOUSE) {
			if(((winch(gameWindow) & A_CHARTEXT) == deadChar)) {
				wprintw(gameWindow,"%c", aliveChar);

				int list[16] = {curry-1, currx-1, curry-1, currx,
								curry-1, currx+1, curry, currx-1,
								curry, currx+1,	curry+1, currx-1,
								curry+1, currx, curry+1, currx+1};

				if(head != NULL) {
					temp = createNewCell(curry, currx, ALIVE);

					if(inLinkedList(head,temp)){
						head = flipInList(head,temp);
						free(temp);
					}else{
						tail = addToList(tail,temp);
					}

					for(int i = 0; i < 16; i+=2) {
						temp = createNewCell(list[i], list[i+1], DEAD); 

						if(!inLinkedList(head,temp)){
							tail = addToList(tail,temp);
						}else{
							free(temp);
						}
					}

				}else {
					temp = createNewCell(curry, currx, ALIVE); 

					head = temp;
					tail = temp;	
					
					for(int i = 0; i < 16; i+=2) {
						temp = createNewCell(list[i], list[i+1], DEAD); 
						tail = addToList(tail,temp);						
					}
					temp = head;
				}
			}else { // current cell is alive
				temp = createNewCell(curry, currx, ALIVE);
				head = flipInList(head,temp);
				free(temp);
				wprintw(gameWindow,"%c", deadChar);
			}
			wrefresh(gameWindow);
		}

		if (ch == 'q'){								// Stops user input if enter is pressed.
			endwin();
			printf("program aborted before game start \n");
			return 0;
		}
	}

	curs_set(0); // makes the cursor invisible
	turns = runGame(&gameWindow, head, tail); 	// This will "run" the game it will, update the gameWindow based on gameLogic.
	free_item(items[0]);
	free_item(items[1]);
	free_menu(menu);
	endwin();
	printf("total turns = %d \n", turns);
	return 0;
}

void setupScreen(){
	char title[] = "The Game of Life";
	char instructions1[] = "Use vim or arrow keys to navigate & e to alter cells";
	char instructions2[] = "Press enter to run, change colors with c";
	char exitMessage[] = "Press 'q' to quit";
	int row, col; // the stdscr window's rows and columns

	getmaxyx(stdscr, row, col); // get rows and columns of stdscr window
	// printing title and instructions to stdscr 
	mvprintw(0, (col-strlen(title))/2, "%s", title); 
	mvprintw(1, (col-strlen(instructions1))/2, "%s", instructions1); 
	mvprintw(2, (col-strlen(instructions2))/2, "%s", instructions2); 
	mvprintw(row-1, (col-strlen(exitMessage))/2, "%s", exitMessage); 
	refresh();
}

void build_color_pairs(){

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
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

char *my_itoa(int i) {
	char *dest;
  	sprintf(dest, "%d", i);
  	return dest;
}