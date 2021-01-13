#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdbool.h>	/* bool */
#include "cell.h"
void changeYX(int ch, int* curry, int* currx, int maxy, int maxx);
void changeCell(int* y, int* x);
void addCells(int* y, int* x);
bool stillAlive(WINDOW *local_win, int gameRow, int gameCol);
int runGame(WINDOW *local_win, int gameRow, int gameCol);
#endif // SUDOKU_HZ
