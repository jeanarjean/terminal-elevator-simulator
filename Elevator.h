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
  void Update();

  void Render();
  void InitRender();
  void Stop();
  void EraseElevatorLag(int y);
  void SetState(int newState);
  const int GetState();
  const int GetHeight();
  bool IsStopped();
  std::vector<Passenger> *getPassengers();
  void Readjust(int readjustHeight);

private:
  int readjustingHeight;
  int current_floor;
  int number_of_floors;
  int state;
  int previous_state;
  int ticksWaited;
  bool stopped;
  std::vector<Passenger> *passengers;

  WINDOW *win;
  int y;
  int x;
};

#endif