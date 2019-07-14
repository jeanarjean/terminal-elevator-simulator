#ifndef FLOOR_H
#define FLOOR_H
#include "vector"

using namespace std;

class Passenger;

class Floor
{
public:
    Floor(int height);
    void Update();
    void Render();
    void AddPassenger(Passenger *passenger);

    // GoGetters
    bool CallFloor();
    void resetFloorCalled();
    bool GetUpButtonState();
    bool GetDownButtonState();
    void CallElevatorUp();
    void CallElevatorDown();
    void ResetUpButton();
    void ResetDownButton();
    vector<Passenger *> *GetPassengers();

    // DEBUG
    int GetHeight();

private:
    int height;
    bool upButtonPressed;
    bool downButtonPressed;
    bool floorIsCalled;
    vector<Passenger *> *passengers;
};

#endif