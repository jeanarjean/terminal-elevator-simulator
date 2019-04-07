// Elevator.h
#ifndef MEDIATOR_H
#include "Elevator.h"
#define MEDIATOR_H

class Mediator
{
  public:
    Mediator();
    void start();

  private:
    Elevator elevator;
};

#endif