#include "Mediator.h"
#include "Elevator.h"
#include "Floor.h"
#include <iostream>
#include "Constants.h"
#include "Passenger.h"
#include <time.h>

Mediator::Mediator()
{
    elevator = new Elevator();
    floors = new std::vector<Floor>;
    for (int i = LINES - 1; i > ELEVATOR_HEIGHT; i = i - FLOOR_HEIGHT)
    {
        Floor floor(i);
        floor.PressDownButton();
        floor.PressUpButton();
        floors->insert(floors->end(), floor);
    }
}

Mediator::~Mediator()
{
    delete elevator;
}

void Mediator::Start()
{
    int milisec = 200; // length of time to sleep, in miliseconds
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;
    int ticksToSpawnPassenger = 0;
    while (1)
    {
        elevator->Tick();

        std::vector<Floor>::iterator floorIt;
        for (floorIt = floors->begin(); floorIt < floors->end(); floorIt++)
        {
            floorIt->Tick();
            if (!elevator->IsStopped())
            {
                if (floorIt->UpButtonPressed() && elevator->GetDirection() == DIRECTION_UP && floorIt->GetHeight() == elevator->GetHeight())
                {
                    move(elevator->GetHeight(), ELEVATOR_HEIGHT);
                    floorIt->ResetUpButton();
                    elevator->Stop();
                }
                if (floorIt->DownButtonPressed() && elevator->GetDirection() == DIRECTION_DOWN && floorIt->GetHeight() == elevator->GetHeight())
                {
                    move(elevator->GetHeight(), ELEVATOR_HEIGHT);
                    floorIt->ResetDownButton();
                    elevator->Stop();
                }
            }

            ticksToSpawnPassenger++;
            if (ticksToSpawnPassenger > TICKS_PASSENGER_SPAWN_INTERVAL)
            {
                ticksToSpawnPassenger = 0;

                vector<Floor>::iterator floorWantsToGoIt = floors->begin();
                std::advance(floorWantsToGoIt, std::rand() % floors->size());

                vector<Floor>::iterator floorSpawnedOnIt = floors->begin();
                std::advance(floorSpawnedOnIt, std::rand() % floors->size());
                while (&(*floorWantsToGoIt) == &(*(floorSpawnedOnIt)))
                {
                    floorSpawnedOnIt = floors->begin();
                    std::advance(floorSpawnedOnIt, std::rand() % floors->size());
                }

                Passenger passenger(&(*floorWantsToGoIt), &(*floorSpawnedOnIt));
                floorSpawnedOnIt->getPassengers()->insert(floorSpawnedOnIt->getPassengers()->end(), passenger);
            }
        }
        refresh();
        nanosleep(&req, (struct timespec *)NULL);
    }
}