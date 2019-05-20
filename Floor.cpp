#include "Floor.h"
#include "Constants.h"
#include "ncurses.h"

Floor::Floor(int height)
{
    Floor::height = height;
}

void Floor::Update()
{

}

void Floor::Render()
{
   move(height, ELEVATOR_WIDTH);
   hline(ACS_HLINE, FLOOR_WIDTH);
}