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