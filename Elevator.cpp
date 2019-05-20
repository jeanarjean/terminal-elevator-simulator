#include "Elevator.h"
#include "Constants.h"


Elevator::Elevator()
{

}

void Elevator::Update()
{

}

void Elevator::Render()
{

}

void Elevator::InitRender()
{
    x = ELEVATOR_STATE_GOING_DOWN;
    y = LINES;
    win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH, y - ELEVATOR_HEIGHT + 1, x);
    leaveok(win, true);
    box(win, 0, 0);
    wrefresh(win);
    refresh();
}