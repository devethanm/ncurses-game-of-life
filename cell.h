#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Cell{
	int x;
	int y;
	bool alive;
	char neighbours[8][8];
	char name[];
};

void setCellYX(struct Cell *cel, int y, int x);
void setCellName(struct Cell *cel);
void flipCell(struct Cell *cel);
bool isAlive(struct Cell *cel);
void setCellLifeState(struct Cell *cel, bool alv);
void addNeighbours(struct Cell *cel, char nbrs[8][8]);

#endif // SUDOKU_H