#include "Elevator.h"
#include "Floor.h"
#include "Passenger.h"
#include "Constants.h"
#include <iostream>

using namespace std;

Elevator::Elevator() : current_floor(0)
{
    number_of_floors = LINES / 5;
    InitRender();
    // state = ELEVATOR_STATE_GOING_UP;
    state = ELEVATOR_STATE_GOING_UP;
    ticksWaited = 0;
    stopped = false;
    passengers = new std::vector<Passenger>;
}

void Elevator::InitRender()
{
    x = ELEVATOR_STATE_GOING_DOWN;
    // y = 20;
    y = LINES;
    win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH, y - ELEVATOR_HEIGHT + 1, x);
    leaveok(win, true);
    box(win, 0, 0);
    wrefresh(win);
    refresh();
}

void Elevator::Update(std::vector<Floor> *floors)
{
    switch (state)
    {
    case ELEVATOR_STATE_IDLE:
        Idle();
        break;
    case ELEVATOR_STATE_GOING_DOWN:
        GoDown(floors);
        break;
    case ELEVATOR_STATE_GOING_UP:
        GoUp(floors);
        break;
    case ELEVATOR_STATE_READJUSTING:
        Readjusting();
        break;
    case ELEVATOR_STATE_STOPPED:
        Stopped();
        break;

    default:
        break;
    }
}

void Elevator::Render()
{
    int elevatorCapacity = ELEVATOR_HEIGHT * ELEVATOR_WIDTH;
    for (int i = 0; i < elevatorCapacity; i++)
    {
        move(i / ELEVATOR_WIDTH - 1, i % ELEVATOR_WIDTH);
        addch(' ');
    }

    int i = 0;
    std::vector<Passenger>::iterator passengerIt;
    for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
    {
        ++i;
        move(y - i / ELEVATOR_WIDTH - 1, i % ELEVATOR_WIDTH);
        addch(passengerIt->getSprite());
    }

    EraseElevatorLag(y + 1);
    EraseElevatorLag(y - ELEVATOR_HEIGHT);
    mvwin(win, y - ELEVATOR_HEIGHT + 1, 0);
    wrefresh(win);
}

void Elevator::Idle()
{
}

void Elevator::GoUp(std::vector<Floor> *floors)
{
    if (y > 3)
    {
        y--;
    }
    std::vector<Floor>::iterator floorIt;
    for (floorIt = floors->begin(); floorIt < floors->end(); floorIt++)
    {
        if (floorIt->GetHeight() == y)
        {
            if (floorIt->UpButtonPressed())
            {
                floorIt->ResetUpButton();
                TransferPassengersToFloor(&(*floorIt));
                AcquirePassengersFromFloor(&(*floorIt));
                Stop();
            }
            else if (ShouldStopForPassengers(&(*floorIt)))
            {
                TransferPassengersToFloor(&(*floorIt));
                AcquirePassengersFromFloor(&(*floorIt));
                Stop();
            }
        }
    }
}

void Elevator::GoDown(std::vector<Floor> *floors)
{
    if (y < LINES - 1)
    {
        y++;
    }
    std::vector<Floor>::iterator floorIt;
    for (floorIt = floors->begin(); floorIt < floors->end(); floorIt++)
    {
        if (floorIt->GetHeight() == y)
        {
            if (floorIt->DownButtonPressed())
            {
                floorIt->ResetUpButton();
                TransferPassengersToFloor(&(*floorIt));
                AcquirePassengersFromFloor(&(*floorIt));
                Stop();
            }
            else if (ShouldStopForPassengers(&(*floorIt)))
            {
                TransferPassengersToFloor(&(*floorIt));
                AcquirePassengersFromFloor(&(*floorIt));
                Stop();
            }
        }
    }
}

void Elevator::Readjusting()
{
    if (y < readjustingHeight)
    {
        y++;
        if (y == readjustingHeight)
        {
            state = ELEVATOR_STATE_GOING_UP;
        }
    }
    else if (y > readjustingHeight)
    {
        y--;
        if (y == readjustingHeight)
        {
            state = ELEVATOR_STATE_GOING_DOWN;
        }
    }
}

void Elevator::Stopped()
{
    ++ticksWaited;
    ticksWaited = ticksWaited + 1;
    move(0, 0);
    if (ticksWaited > TICKS_TO_STOP)
    {
        state = previous_state;
    }
}

void Elevator::EraseElevatorLag(int y)
{
    move(y, 0);
    for (int i = 0; i < ELEVATOR_WIDTH; ++i)
    {
        addch(' ');
    }
    move(y, 0);
}

const int Elevator::GetHeight()
{
    return y;
}

const int Elevator::GetState()
{
    return state;
}

void Elevator::SetState(int newState)
{
    state = newState;
}

void Elevator::Stop()
{
    ticksWaited = 0;
    previous_state = state;
    state = ELEVATOR_STATE_STOPPED;
}

bool Elevator::IsStopped()
{
    return stopped;
}

std::vector<Passenger> *Elevator::getPassengers()
{
    return passengers;
}

void Elevator::Readjust(int readjustHeight)
{
    state = ELEVATOR_STATE_READJUSTING;
    readjustingHeight = readjustHeight;
}

void Elevator::TransferPassengersToFloor(Floor *floor)
{
    std::vector<Passenger>::iterator passengerIt;
    for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
    {
        if (passengerIt->getFlootWantsToGo() == floor)
        {
            passengers->erase(passengerIt);
        }
    }
}

void Elevator::AcquirePassengersFromFloor(Floor *floor)
{
    std::vector<Passenger>::iterator passengerIt;
    for (passengerIt = floor->getPassengers()->begin(); passengerIt < floor->getPassengers()->end(); passengerIt++)
    {
        if (passengerIt->getDirection() == state)
        {
            passengers->insert(passengers->end(), *(passengerIt));
            floor->getPassengers()->erase(passengerIt);
        }
    }
}

bool Elevator::ShouldStopForPassengers(Floor *floor)
{
    std::vector<Passenger>::iterator passengerIt;
    bool shouldStop = false;
    for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
    {
        if (passengerIt->getFlootWantsToGo() == floor)
        {
            shouldStop = true;
        }
    }
    return shouldStop;
}