#include <ncurses.h>
#include <stdio.h>
#include "sudoku.h"

WINDOW *create_board(int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(19, 37, starty, startx);
	box(local_win, 0 , 0);		

	wrefresh(local_win);						/* Show that box */

	return local_win;
}

void draw_grid(WINDOW* grid)
{
	int i, j;

	for(i = 0;i < 10;i++)
	{
		for(j = 0;j < 10;j++)
		{
			if(i == 0 && j == 0)
				waddch(grid, ACS_ULCORNER);
			else if(i == 0 && j == 9)
				waddch(grid, ACS_URCORNER);
			else if(i == 9 && j == 9)
				waddch(grid, ACS_LRCORNER);
			else if(i == 9 && j == 0)
				waddch(grid, ACS_LLCORNER);
			else if(i == 0)
				waddch(grid, ACS_TTEE);
			else if(i == 9)
				waddch(grid, ACS_BTEE);
			else if(j == 0)
				waddch(grid, ACS_LTEE);
			else if(j == 9)
				waddch(grid, ACS_RTEE);
			else
				waddch(grid, ACS_PLUS);
			if(j < 9)
			{
				waddch(grid, ACS_HLINE);
				waddch(grid, ACS_HLINE);
				waddch(grid, ACS_HLINE);
			}
			
		}
		for(j = 0;j < 10 && i < 9;j++)
		{
			if(j > 0)
				wprintw(grid, "   ");
			waddch(grid, ACS_VLINE);
		}
	}
}