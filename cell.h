#ifndef CELL_H
#define CELL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Cell {
	int y;
	int x;
	bool alive;
	struct Cell* next; // used to point to the next element in the linked list
};

void setCellYX(struct Cell *cel, int y, int x);
void setCellName(struct Cell *cel);
void flipCell(struct Cell *cel);
bool isAlive(struct Cell *cel);

#endif // SUDOKU_H
