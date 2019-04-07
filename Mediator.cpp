#include "Mediator.h"

Mediator::Mediator()
{
    Elevator elevator;
}

void Mediator::start()
{
    while(1){
        elevator.tick();
    }
}