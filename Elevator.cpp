#include "Elevator.h"
#include <iostream>

using namespace std;

Elevator::Elevator(int floor) : number_of_floors(floor), current_floor(0)
{
  InitRender();
}

void Elevator::Tick() 
{
  Render();
}

int Elevator::GetCurrentFloor()
{
    return current_floor;
}

int Elevator::GetNumberOfFloors()
{
    return number_of_floors;
}

void Elevator::InitRender()
{
  x = 0;
  y = LINES-ELEVATOR_HEIGHT;
  win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH , y, x);
  leaveok(win, true);
  box(win,0,0);

  wrefresh(win);
}

void Elevator::Render()
{
  MoveUpRender();
  wrefresh(win);
  refresh();
}

void Elevator::MoveUpRender()
{
  //TODO: Once state implemented,  Y will not be changed here
  move(y+ELEVATOR_HEIGHT,0);
  clrtoeol();
  if(y > 5){
    mvwin(win, --y, 0);
  }
}

void Elevator::MoveDownRender()
{
  //TODO: Once state implemented,  Y will not be changed here
  move(y-1,0);
  clrtoeol();
  if(y < LINES - ELEVATOR_HEIGHT){
    mvwin(win, ++y, 0);
  }
}