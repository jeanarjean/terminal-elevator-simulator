#include "Elevator.h"
#include "Passenger.h"
#include "Constants.h"
#include "Floor.h"

Elevator::Elevator()
{
    state = ELEVATOR_STATE_GOING_UP;
    requestedFloors = new map<int, Floor *>;
    passengers = new vector<Passenger *>;
}

// HOLY FINITE STATE AUTOMATA

void Elevator::Update(map<int, Floor *> *floors)
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

void Elevator::GoUp(map<int, Floor *> *floors)
{
    map<int, Floor *>::iterator floorIt;
    if (y > 3)
    {
        y--;
    }
    floorIt = floors->find(y);
    if (floorIt != floors->end())
    {
        if (floorIt->second->GetUpButtonState())
        {
            floorIt->second->ResetUpButton();
            PickupPassengersFromFloor(floorIt->second);
            DropOffPassengersOnFloor(floorIt->second);
            Stop();
        }
        else if (floorIt->second == floors->begin()->second)
        {
            state = ELEVATOR_STATE_GOING_DOWN;
            floorIt->second->ResetDownButton();
            PickupPassengersFromFloor(floorIt->second);
            Stop();
        }
    }
}

void Elevator::GoDown(map<int, Floor *> *floors)
{
    map<int, Floor *>::iterator floorIt;
    if (y < LINES)
    {
        y++;
    }
    floorIt = floors->find(y);
    if (floorIt != floors->end())
    {
        if (floorIt->second->GetDownButtonState())
        {
            floorIt->second->ResetDownButton();
            PickupPassengersFromFloor(floorIt->second);
            DropOffPassengersOnFloor(floorIt->second);
            Stop();
        }
        else if (floorIt->second == floors->rbegin()->second)
        {
            state = ELEVATOR_STATE_GOING_UP; // NEEDS ANOTHER ELESE OR SOMETHING
            floorIt->second->ResetUpButton();
            PickupPassengersFromFloor(floorIt->second);
            Stop();
        }
    }
}

void Elevator::Readjusting()
{
    //TODO, change readjustingHeight
    int readjustingHeight = 2;
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

void Elevator::Idle()
{
}

void Elevator::Stop()
{
    ticksWaited = 0;
    previous_state = state;
    state = ELEVATOR_STATE_STOPPED;
}

void Elevator::DropOffPassengersOnFloor(Floor *floor)
{
    vector<Passenger *>::iterator passengerIt;
    for (passengerIt = passengers->begin(); passengerIt < passengers->end();)
    {
        if ((*passengerIt)->GetRequestedFloorHeight() == floor->GetHeight())
        {
            passengers->erase(passengerIt);
        }
        else
        {
            ++passengerIt;
        }
    }
}

void Elevator::PickupPassengersFromFloor(Floor *floor)
{
    vector<Passenger *>::iterator passengerIt;
    for (passengerIt = floor->GetPassengers()->begin(); passengerIt != floor->GetPassengers()->end();)
    {
        if ((*passengerIt)->GetDirection() == state)
        {
            passengers->insert(passengers->end(), *passengerIt);
            passengerIt = floor->GetPassengers()->erase(passengerIt);
        }
        else
        {
            ++passengerIt;
        }
    }
}

// RENDER
void Elevator::Render()
{
    int i = 0;
    std::vector<Passenger*>::iterator passengerIt;
    for (passengerIt = passengers->begin(); passengerIt < passengers->end(); passengerIt++)
    {
        ++i;
        move(y - i / ELEVATOR_WIDTH - 1, i % ELEVATOR_WIDTH);
        addch((*passengerIt)->GetSprite());
    }

    EraseElevatorRenderLag(y + 1);
    EraseElevatorRenderLag(y - ELEVATOR_HEIGHT);
    mvwin(win, y - ELEVATOR_HEIGHT + 1, 0);
    wrefresh(win);
}

void Elevator::InitRender()
{
    x = ELEVATOR_STATE_GOING_DOWN;
    y = LINES;
    win = newwin(ELEVATOR_HEIGHT, ELEVATOR_WIDTH, y - ELEVATOR_HEIGHT + 1, x);
    leaveok(win, true);
    box(win, 0, 0);
    wrefresh(win);
    refresh();
}

void Elevator::EraseElevatorRenderLag(int height)
{
    move(height, 0);
    for (int i = 0; i < ELEVATOR_WIDTH; ++i)
    {
        addch(' ');
    }
    move(height, 0);
}

map<int, Floor *> *Elevator::GetRequestFloors()
{
    return requestedFloors;
}