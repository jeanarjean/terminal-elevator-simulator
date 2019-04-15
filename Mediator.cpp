#include "Mediator.h"
#include "Elevator.h"
#include "time.h"

using namespace std;

Mediator::Mediator()
{
    elevator = new Elevator();
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
    while(1){
        nanosleep(&req, (struct timespec *)NULL);

        elevator->Tick();
    }
}