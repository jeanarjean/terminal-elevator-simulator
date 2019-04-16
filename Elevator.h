// Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "ncurses.h"

using namespace std;

class Elevator
{
  private:
    int current_floor;
    int number_of_floors;
    int direction;
    int ticksWaited;

    WINDOW *win; 
    int y;
    int x;


    void MoveUpRender();
    void MoveDownRender();

  public:
    Elevator();
    void Tick();

    void Render();
    void InitRender();
    void EraseElevatorLag(int y);
};

#endif