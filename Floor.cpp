#include "Floor.h"
#include "Constants.h"
#include <ncurses.h>

Floor::Floor(int height) : height(height)
{
   InitRender();
}

void Floor::InitRender()
{
   move(height,ELEVATOR_WIDTH);
   hline(ACS_HLINE, FLOOR_WIDTH);
}