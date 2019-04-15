// Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stack>
#include "ncurses.h"


using namespace std;

class Elevator
{
  private:
    int current_floor;
    int number_of_floors;

    stack<int> floorOrdered;
    WINDOW *win; 
    int y;
    int x;

    const int ELEVATOR_HEIGHT = 5;
    const int ELEVATOR_WIDTH = 5;

    void MoveUpRender();
    void MoveDownRender();

    bool movingUp;
    bool movingDown;

  public:
    Elevator();
    void Tick();
    int GetNumberOfFloors();
    int GetCurrentFloor();

    void Render();
    void InitRender();
};

#endif