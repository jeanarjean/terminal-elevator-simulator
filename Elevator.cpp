#include "Elevator.h"
#include <iostream>

using namespace std;

Elevator::Elevator() : current_floor(0)
{
  number_of_floors = LINES/5;
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
  // y = LINES-ELEVATOR_HEIGHT;
  y = 0;
  win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH , y, x);
  leaveok(win, true);
  box(win,0,0);

  wrefresh(win);
}

void Elevator::Render()
{
  MoveDownRender();
  wrefresh(win);
  refresh();
}

void Elevator::MoveUpRender()
{
  //TODO: Once state implemented,  Y will not be changed here
  if(y > 5){
    move(y+ELEVATOR_HEIGHT,0);
    clrtoeol();
    mvwin(win, --y, 0);
  }
}

void Elevator::MoveDownRender()
{
  //TODO: Once state implemented,  Y will not be changed here
  if(y < LINES - ELEVATOR_HEIGHT - 1){
    move(y,0);
    clrtoeol();
    mvwin(win, ++y, 0);
  }
}