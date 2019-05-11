#include "Mediator.h"
#include "Elevator.h"
#include "Floor.h"
#include "Constants.h"
#include "Passenger.h"
#include <iostream>
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
    ticksToSpawnPassenger = 0;
}

Mediator::~Mediator()
{
    delete elevator;
}

void Mediator::Run()
{
    int milisec = 200; // length of time to sleep, in miliseconds
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;
    while (1)
    {
        Update();
        Render();
        nanosleep(&req, (struct timespec *)NULL);
    }
}

void Mediator::Update()
{

        std::vector<Floor>::iterator floorIt;
        for (floorIt = floors->begin(); floorIt < floors->end(); floorIt++)
        {
            floorIt->Update();
            if (!elevator->IsStopped())
            {
                if (floorIt->GetHeight() == elevator->GetHeight())
                {
                    if (floorIt->UpButtonPressed() && elevator->GetState() == ELEVATOR_STATE_GOING_UP)
                    {
                        floorIt->ResetUpButton();
                        elevator->Stop();
                        TransferFromElevatorToFloor(elevator, &(*floorIt));
                        TransferFromFloorToElevator(elevator, &(*floorIt));
                    }
                    if (floorIt->DownButtonPressed() && elevator->GetState() == ELEVATOR_STATE_GOING_DOWN)
                    {
                        floorIt->ResetDownButton();
                        elevator->Stop();
                        TransferFromElevatorToFloor(elevator, &(*floorIt));
                        TransferFromFloorToElevator(elevator, &(*floorIt));
                    }
                    if (DetermineIfShouldStopForPassengers(elevator, &(*floorIt)))
                    {
                        elevator->Stop();
                        TransferFromElevatorToFloor(elevator, &(*floorIt));
                        TransferFromFloorToElevator(elevator, &(*floorIt));
                    }
                    DetermineElevatorDirection();
                }
            }
        }
        elevator->Update();
        SpawnPassenger();
        refresh();
    
}

void Mediator::Render()
{

}

bool Mediator::DetermineIfShouldStopForPassengers(Elevator *elevator, Floor *floor)
{
    std::vector<Passenger>::iterator passengerIt;
    bool shouldStop = false;
    for (passengerIt = elevator->getPassengers()->begin(); passengerIt < elevator->getPassengers()->end(); passengerIt++)
    {
        if (passengerIt->getFlootWantsToGo() == floor)
        {
            shouldStop = true;
        }
    }
    return shouldStop;
}

void Mediator::TransferFromElevatorToFloor(Elevator *elevator, Floor *floor)
{
    std::vector<Passenger>::iterator passengerIt;
    for (passengerIt = elevator->getPassengers()->begin(); passengerIt < elevator->getPassengers()->end(); passengerIt++)
    {
        if (passengerIt->getFlootWantsToGo() == floor)
        {
            elevator->getPassengers()->erase(passengerIt);
        }
    }
}

void Mediator::TransferFromFloorToElevator(Elevator *elevator, Floor *floor)
{
    std::vector<Passenger>::iterator passengerIt;
    for (passengerIt = floor->getPassengers()->begin(); passengerIt < floor->getPassengers()->end(); passengerIt++)
    {
        if (passengerIt->getDirection() == elevator->GetState())
        {
            elevator->getPassengers()->insert(elevator->getPassengers()->end(), *(passengerIt));
            floor->getPassengers()->erase(passengerIt);
        }
    }
}

void Mediator::SpawnPassenger()
{
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

void Mediator::DetermineElevatorDirection()
{
    std::vector<Floor>::iterator floorIt;

    if (elevator->GetState() == ELEVATOR_STATE_GOING_UP)
    {
        bool floorAboveToServeSameDirection = false;
        bool floorAboveToServeDifferentDirection = false;
        bool floorBelowToServeDifferentDirection = false;
        int highestFloorThatHasToGoDown = LINES;
        for (floorIt = floors->begin(); floorIt < floors->end(); floorIt++)
        {
            if (floorIt->GetHeight() < elevator->GetHeight())
            {
                if (floorIt->UpButtonPressed())
                {
                    floorAboveToServeSameDirection = true;
                }
                if (floorIt->DownButtonPressed())
                {
                    floorAboveToServeDifferentDirection = true;
                    if (floorIt->GetHeight() < highestFloorThatHasToGoDown)
                    {
                        highestFloorThatHasToGoDown = floorIt->GetHeight();
                    }
                }
            }
            if (floorIt->GetHeight() >= elevator->GetHeight() && floorIt->DownButtonPressed())
            {
                floorBelowToServeDifferentDirection = true;
            }
        }
        if (floorAboveToServeSameDirection)
        {
            elevator->SetState(ELEVATOR_STATE_GOING_UP);
        }
        else if (!floorAboveToServeSameDirection && floorAboveToServeDifferentDirection)
        {
            elevator->Readjust(highestFloorThatHasToGoDown);
        }
        else if (floorBelowToServeDifferentDirection)
        {
            elevator->SetState(ELEVATOR_STATE_GOING_DOWN);
        }
        else
        {
            elevator->SetState(ELEVATOR_STATE_IDLE);
        }
    }

    if (elevator->GetState() == ELEVATOR_STATE_GOING_DOWN)
    {
        bool floorBelowToServeSameDirection = false;
        bool floorBelowToServeDifferentDirection = false;
        bool floorAboveToServeDifferentDirection = false;
        int lowestFloorThatHasToGoDown = 0;
        for (floorIt = floors->begin(); floorIt < floors->end(); floorIt++)
        {
            if (floorIt->GetHeight() > elevator->GetHeight())
            {
                if (floorIt->DownButtonPressed())
                {
                    floorBelowToServeSameDirection = true;
                }
                if (floorIt->UpButtonPressed())
                {
                    floorBelowToServeDifferentDirection = true;
                    if (floorIt->GetHeight() > lowestFloorThatHasToGoDown)
                    {
                        lowestFloorThatHasToGoDown = floorIt->GetHeight();
                    }
                }
            }
            if (floorIt->GetHeight() <= elevator->GetHeight() && floorIt->UpButtonPressed())
            {
                floorAboveToServeDifferentDirection = true;
            }
        }
        if (floorBelowToServeSameDirection)
        {
            elevator->SetState(ELEVATOR_STATE_GOING_DOWN);
        }
        else if (!floorBelowToServeSameDirection && floorBelowToServeDifferentDirection)
        {
            elevator->Readjust(lowestFloorThatHasToGoDown);
        }
        else if (floorAboveToServeDifferentDirection)
        {
            elevator->SetState(ELEVATOR_STATE_GOING_UP);
        }
        else
        {
            elevator->SetState(ELEVATOR_STATE_IDLE);
        }
    }
}