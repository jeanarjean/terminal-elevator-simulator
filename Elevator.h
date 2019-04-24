// Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "ncurses.h"

using namespace std;

class Elevator
{
  public:
    Elevator();
    void Tick();

    void Render();
    void InitRender();
    void Stop();
    void EraseElevatorLag(int y);
    int GetDirection();
    int GetHeight();
    bool IsStopped();

  private:
    int current_floor;
    int number_of_floors;
    int direction;
    int ticksWaited;
    bool stopped;

    WINDOW *win; 
    int y;
    int x;


    void MoveUpRender();
    void MoveDownRender();
};

#endif