#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdbool.h>	/* bool */
#include "cell.h"

int runGame(WINDOW **local_win, struct Cell* head, struct Cell* back);
bool inLinkedList(struct Cell* front, struct Cell* cel);
bool aliveInList(struct Cell* front, struct Cell* cel);
bool stillAlive(struct Cell* front);
struct Cell* flipInList(struct Cell* front, struct Cell* cel);
struct Cell* addToList(struct Cell* back, struct Cell* cel);
struct Cell* createNewCell(int celly, int cellx, bool alive);
void changeYX(int ch, int* curry, int* currx, int maxy, int maxx);
void changeCell(struct Cell* cel);
void printList(struct Cell* cel);
void build_color_pairs();
void addCells(int celly, int cellx, int maxy, int maxx);
#endif // GAMELOGIC_H
