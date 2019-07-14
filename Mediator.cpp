#include "Mediator.h"
#include "Elevator.h"
#include "Floor.h"
#include "Passenger.h"
#include "Constants.h"
#include <ncurses.h>

Mediator::Mediator()
{
    elevator = new Elevator();
    floors = new map<int, Floor *>;
    for (int i = LINES - 1; i > ELEVATOR_HEIGHT; i = i - FLOOR_HEIGHT)
    {
        Floor *floor = new Floor(i);
        floors->insert({i, floor});
    }
    currentTick = 0;
}

void Mediator::Run()
{
    int milisec = 200; // length of time to sleep, in miliseconds
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;

    InitRender();
    while (1)
    {
        Update();
        Render();
        nanosleep(&req, (struct timespec *)NULL);
    }
}

void Mediator::Update()
{
    elevator->Update(floors);
    for (auto x : *floors)
    {
        x.second->Update();
    }
    SpawnPassenger();
}

void Mediator::Render()
{
    elevator->Render();
    for (auto x : *floors)
    {
        x.second->Render();
    }
    refresh();
}

void Mediator::InitRender()
{
    elevator->InitRender();
}

void Mediator::SpawnPassenger()
{
    currentTick++;
    if (currentTick > shouldSpawnOnThisTick)
    {
        currentTick = 0;
        map<int, Floor *>::iterator floorIt;
        Floor *targetedFloor;
        int direction;
        int spawnFloorMapOrder = rand_between(0, floors->size());
        int requestedFloorHeight;

        if (spawnFloorMapOrder == 0)
        {
            direction = ELEVATOR_STATE_GOING_UP;
        }
        else if (spawnFloorMapOrder == floors->size() - 1)
        {
            direction = ELEVATOR_STATE_GOING_DOWN;
        }
        else
        {
            direction = rand_between(ELEVATOR_STATE_GOING_DOWN, ELEVATOR_STATE_GOING_UP);
            addch(direction);
        }

        floorIt = floors->find(LINES - 1 - (spawnFloorMapOrder * FLOOR_HEIGHT));
        switch (direction)
        {
        case ELEVATOR_STATE_GOING_DOWN:
            requestedFloorHeight = rand_between(spawnFloorMapOrder + 1, floors->size());
            floorIt->second->CallElevatorDown();
            break;
        case ELEVATOR_STATE_GOING_UP:
            requestedFloorHeight = rand_between(spawnFloorMapOrder, floors->size() - 1);
            floorIt->second->CallElevatorUp();
            break;
        default:
            break;
        }
        if (floorIt != floors->end())
        {
            floorIt->second->AddPassenger(new Passenger(requestedFloorHeight, direction));
        }

        direction = 2;
    }
}

int Mediator::rand_between(int min, int max)
{
    return rand() % max + min;
}