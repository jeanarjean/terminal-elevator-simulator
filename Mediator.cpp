#include "Mediator.h"
#include "Elevator.h"
#include "Floor.h"
#include <time.h>

Mediator::Mediator()
{
    elevator = new Elevator();
    floors = new std::vector<Floor>;
    for (int i = LINES-1; i > 0; i = i - 5)
    {
        floors->assign(i, Floor(i));
    }
}

Mediator::~Mediator()
{
    delete elevator;
}

void Mediator::start()
{
    int milisec = 200; // length of time to sleep, in miliseconds
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;
    while (1)
    {
        nanosleep(&req, (struct timespec *)NULL);
        elevator->Tick();
    }
}