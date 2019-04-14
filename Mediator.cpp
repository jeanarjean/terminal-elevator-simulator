#include "Mediator.h"
#include "Elevator.h"

Mediator::Mediator()
{
    elevator = new Elevator(5);
}

Mediator::~Mediator()
{
    delete elevator;
}

void Mediator::start()
{
    while(1){
        elevator->Tick();
    }
}