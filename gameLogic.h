#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdbool.h>	/* bool */
#include "cell.h"
void changeYX(int ch, int* curry, int* currx, int maxy, int maxx);
void changeCell(struct Cell* cel);
void printList();
struct Cell* createNewCell(int celly, int cellx, bool alive);
void addCells(int celly, int cellx, int maxy, int maxx);
bool stillAlive(WINDOW *local_win, int gameRow, int gameCol, struct Cell* head);
int runGame(WINDOW *local_win, int gameRow, int gameCol, struct Cell* head);
#endif // SUDOKU_HZ
