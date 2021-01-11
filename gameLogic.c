#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "gameLogic.h"

const bool ALIVE = true;
const bool DEAD = false;
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
		return;
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

	while(stillAlive(gameWindow, gameRow, gameCol)){
		
		// update window based on rules of the game.



		//filler code for now.
		if (turns == 50000)
		{
			return -1;
		}
		usleep(1000000);
		turns = turns + 1;
		//=================
	}
	return turns;
}
