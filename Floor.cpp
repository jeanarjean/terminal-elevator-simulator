#include "Floor.h"
#include "ncurses.h"

Floor::Floor(int height) : height(height)
{
   InitRender();
}

void Floor::InitRender()
{
   move(height,5);
   hline(ACS_HLINE, 5);
}