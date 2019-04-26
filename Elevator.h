// Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "ncurses.h"
#include <vector>

using namespace std;

class Passenger;

class Elevator
{
  public:
    Elevator();
    void Tick();

    void Render();
    void InitRender();
    void Stop();
    void EraseElevatorLag(int y);
    void SetDirection(int newDirection);
    const int GetDirection();
    const int GetHeight();
    bool IsStopped();
    std::vector<Passenger>* getPassengers();


  private:
    int current_floor;
    int number_of_floors;
    int direction;
    int ticksWaited;
    bool stopped;
    std::vector<Passenger> *passengers;

    WINDOW *win; 
    int y;
    int x;


    void MoveUpRender();
    void MoveDownRender();
};

#endif