// Elevator.h
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "ncurses.h"
#include <vector>

using namespace std;

class Passenger;
class Floor;

class Elevator
{
public:
  Elevator();
  void Update(std::vector<Floor> *Floors);

  void Render();
  void InitRender();
  void Stop();
  void Readjust();
  void EraseElevatorLag(int y);
  void SetState(int newState);
  const int GetState();
  const int GetHeight();
  bool IsStopped();
  std::vector<Passenger> *getPassengers();
  void Readjust(int readjustHeight);

private:
  void GoUp(std::vector<Floor> *floors);
  void GoDown(std::vector<Floor> *floors);
  void Idle();
  void Readjusting();
  void Stopped();

  bool ShouldStopForPassengers(Floor *floor);
  void TransferPassengersToFloor(Floor *floor);
  void AcquirePassengersFromFloor(Floor *floor);

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