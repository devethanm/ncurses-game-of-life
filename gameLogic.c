#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "gameLogic.h"
#include "cell.h"

const bool ALIVE = true;
const bool DEAD = false;
const char aliveChar = '@';
const char deadChar = '*';
// head is set to NULL at first, and is then assigned the address of the first cell 
// that is added by the user. see addCells method

MEVENT event;


// Use pointers to update current x,y
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

void printList(struct Cell* cel) {
	struct Cell* temp = cel;
	while(temp != NULL) {
		// printf("IN THE LOOP \n");
		printf(" (x=%d - y=%d) ", temp->x, temp->y);
		temp = temp->next;
	}
}

struct Cell* createNewCell(int celly, int cellx, bool alive) {
	struct Cell* ret = malloc(sizeof(struct Cell));
	ret->y = celly;
	ret->x = cellx;
	ret->alive = alive;
	ret->shouldDie = false;
	return ret;
}

bool inLinkedList(struct Cell* front, struct Cell* cel){
	struct Cell* temp = front;
	while(temp != NULL){
		if (areEqual(temp, cel))
		{
			return true;
		}
		temp = temp->next;
	}
	return false;
}

struct Cell* addToList(struct Cell* back, struct Cell* cel){
	back->next = cel;
	return cel;
}

struct Cell* flipInList(struct Cell* front, struct Cell* cel){
	struct Cell* temp = front;
	while(temp != NULL){
		if (areEqual(temp, cel))
		{
			flipCell(temp);
			break;
		}
		temp = temp->next;
	}
	return front;
}

bool aliveInList(struct Cell* front, struct Cell* cel){
	struct Cell* temp = front;
	while(temp != NULL){
		if (areEqual(temp, cel))
		{
			return temp->alive;
		}
		temp = temp->next;
	}
	return false;
}


// This checks to see if there is atleast 1 live cell, and returns DEAD if there isn't.
bool stillAlive(struct Cell* front) {
	struct Cell* temp = front;
	while(temp != NULL){
		if (isAlive(temp))
		{
			return ALIVE;
		}
		temp = temp->next;
	}
	return DEAD;
}
// This is where the game changes based on the Rules of life.
// I currently have code that just stops it after 3 turns(to be changed later)
int runGame(WINDOW **gameWindow, struct Cell* front, struct Cell* back) {
	int turns = 0;
	nodelay(*gameWindow,TRUE);
	int colorValue = 1;
	while(stillAlive(front)) {
		struct Cell* temp = front;

		// update window based on rules of the game.
		// Any live cell with two or three live neighbours survives.
		while(temp != NULL) {
			int list[16] = {temp->y-1, temp->x-1, temp->y-1, temp->x, 
							temp->y-1, temp->x+1, temp->y, temp->x-1, 
							temp->y, temp->x+1, temp->y+1, temp->x-1, 
							temp->y+1, temp->x, temp->y+1, temp->x+1};

			int count = 0; // counts how many live neighbors a cell has

		
			struct Cell* tempCheck;
			for(int i = 0; i < 16; i+=2) {

				tempCheck = createNewCell(list[i], list[i+1], DEAD);
				
				if(!inLinkedList(front,tempCheck)){
					// NOT IN LINKED LIST and living
					if (isAlive(temp))
					{
						back = addToList(back, tempCheck);
					}
				}else{
					// IN LINKED LIST
					if(aliveInList(front,tempCheck)) { 
						count++;
					}
					free(tempCheck);
				}

			}

			if(isAlive(temp)) {
				if(count == 2 || count == 3) {
					printf("%d", count);
				
					temp->shouldDie = false;
				}
				else {
					temp->shouldDie = true;
				}

			}else{
				if(count == 3) {
					temp->shouldDie = true;
				}
			}
			

			temp = temp->next;
		}
    	// All other live cells die in the next generation. 
		// Similarly, all other dead cells stay dead.
		temp = front;
		while(temp != NULL) {
			if(temp->shouldDie){
				flipCell(temp);
				temp->shouldDie = false;
				if(isAlive(temp)) {
					
					mvwprintw(*gameWindow, temp->y, temp->x, "%c", aliveChar);	
				}
				else {
					
					mvwprintw(*gameWindow, temp->y, temp->x, "%c", deadChar);
				}
			}
			temp = temp->next;
		}			
		
		wrefresh(*gameWindow);
		int ch = wgetch(*gameWindow);
		// Change color if c is pressed.
		if (ch =='c'){
			colorValue++;
			wattron(*gameWindow,COLOR_PAIR(colorValue));
			if (colorValue ==8){ colorValue = 1; }
		}
		if (ch =='q'){
			break;
		}
		usleep(1000000);
		turns = turns + 1;

	}
	nodelay(*gameWindow,FALSE);
	printList(front);
	return turns;
}