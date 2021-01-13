#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "gameLogic.h"
#include "cell.h"

const bool ALIVE = true;
const bool DEAD = false;
struct Cell* head = NULL; // global variable for the head of the linked list of cells
// head is set to NULL at first, and is then assigned the address of the first cell that is added by the user
// see addCells method

MEVENT event;
// void changeYX(int ch, int* curry, int* currx, int maxy, int maxx);
// void changeCell(int* y, int* x); // not sure if all methods should be declared up here im putting this here for now
// maybe we should move all game of life logic related methods to gameLogic.h and gameLogic.c or something
// Use pointers to update current x,y
// not sure if maxy and x should be pointers we can optimize later
void changeYX(int ch, int *curry, int *currx, int maxy, int maxx) {
	        
	switch (ch){
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
	            	*curry = *curry-1;
		    }
            break;
        case 'j': // (down)
		    if(*curry < maxy - 2) {
	            	*curry = *curry+1;
		    }
            break;

        // MOUSE EVENTS
		case KEY_MOUSE:
			if(getmouse(&event) == OK) {
				if(event.bstate & BUTTON1_CLICKED) {
					*curry = event.y-3; // mouse y when clicked
					*currx = event.x; // mouse x when clicked
				}
			}
			break;
	}
}

void changeCell(int *y, int *x) {
	// this method is used to change cells within the activeCells list from dead to alive, or alive to dead
	return;
}

void addCells(int* y, int* x) {
	// This method is called when the user clicks/or pressed e to add a cell
	// sends the x and y coordinates of the cell they were on
	// then adds that cell and its neighbors to activeCells
	// however, only the cell they selected will be alive
	
	if(head != NULL) {
		// if head is = NULL, then we know this is the first cell being added,
		// and we don't have to make sure its neighbors aren't already in the list

	}
	else {
		// the first time a user clicks on a cell, we have to add a total of 9 cells to the list
		// one for the cell they selected, and 8 for all of its neighboring cells
		// im adding the middle cell first, then going top to bottom, left to right, 
		// skipping the middle cell
		// struct Cell* c1 = (struct Cell*) malloc(sizeof(struct Cell));
		
		// below is what im trying to do but it throws errors im not sure how we are supposed to define new cells
	
				
		// struct Cell c1;
		// c1.y = y; c1.x = x;
		// printf("%d\n", c1.y);	
	}
}

// This checks to see if there is atleast 1 live cell, and returns DEAD if there isn't.
bool stillAlive(WINDOW *gameWindow, int gameRow, int gameCol){
	for(int i = 0; i < gameRow; i++) {
		for(int j = 0; j < gameCol; j++) {

			wmove(gameWindow,i,j);
			if (((winch(gameWindow) & A_CHARTEXT) == '@')){
				wprintw(gameWindow,"%c",'*');
				wrefresh(gameWindow);
				return ALIVE;
			}
		}
	}
	return DEAD;
}
// This is where the game changes based on the Rules of life.
// I currently have code that just stops it after 3 turns(to be changed later)
int runGame(WINDOW *gameWindow, int gameRow, int gameCol){
	int turns = 0;
	nodelay(gameWindow,TRUE);
	while(stillAlive(gameWindow, gameRow, gameCol)){
		
		// update window based on rules of the game.



		//filler code for now.
		if (turns == 50000)
		{
			return -1;
		}
		usleep(100000);
		if (wgetch(gameWindow)=='q')
		{
			nodelay(gameWindow,FALSE);
			return turns;
		}
		usleep(1000000);
		turns = turns + 1;
		//=================
	}
	return turns;
}
