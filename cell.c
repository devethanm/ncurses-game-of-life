#include "cell.h"

// Flips alive to dead, or dead to alive.
void flipCell(struct Cell *cel){
	cel->alive = !cel->alive;
}

bool isAlive(struct Cell *cel){
	return cel->alive;
}

void setCellLifeState(struct Cell *cel, bool alv){
	cel->alive = alv;
}

void setCellYX(struct Cell *cel, int y, int x){
	cel->y = y;
	cel->x = x;
}

bool areEqual(struct Cell *cel1, struct Cell *cel2){

	if (cel1->x == cel2->x && cel1->y == cel2->y){
		return true;
	}
	return false;
}

/*
void setCellName(struct Cell *cel){
	char str[8];
	sprintf(str, "%d,%d", cel->y,cel->x);
	//strcpy(cel->name, str);
}

void addNeighbours(struct Cell *cel, char nbrs[8][8]){
	for (int i = 0; i < 8; ++i)
	{
		// strcpy(cel->neighbours[i], nbrs[i]);
	}
}
*/

/* HOW TO USE CELLS W/ FUNCTIONS

	struct Cell* dummyCell = (struct Cell*) malloc(sizeof(struct Cell));
	char nbrs[8][8] = 	{
							"1,2",
							"2,2",
							"2,1",
							"0,1",
							"1,0",
							"0,0",
							"2,0",
							"0,2"
						};

	
	setCellYX(dummyCell,1,1);
	setCellLifeState(dummyCell,true);
	setCellName(dummyCell);
	addNeighbours(dummyCell,nbrs);
*/

