#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdbool.h>	/* bool */
#include "cell.h"
void changeYX(int ch, int* curry, int* currx, int maxy, int maxx);
void changeCell(struct Cell* cel);
void printList(struct Cell* cel);
struct Cell* createNewCell(int celly, int cellx, bool alive);
bool inLinkedList(struct Cell* front, struct Cell* cel);
bool flipInList(struct Cell* front, struct Cell* cel);
void addCells(int celly, int cellx, int maxy, int maxx);
bool stillAlive(struct Cell* front);
struct Cell* addToList(struct Cell* back, struct Cell* cel);
int runGame(WINDOW **local_win, struct Cell* head, struct Cell* back);
#endif // SUDOKU_HZ
