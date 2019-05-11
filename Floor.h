#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "Passenger.h"

class Floor
{
    public: 
    Floor(int height);

    void Update();
    void PressUpButton();
    void PressDownButton();
    void ResetUpButton();
    void ResetDownButton();
    int GetHeight();
    bool UpButtonPressed();
    bool DownButtonPressed();
    std::vector<Passenger>* getPassengers();

    private:
    void InitRender();

    bool upButtonPressed;
    bool downButtonPressed;
    int height;
    std::vector<Passenger> *passengers;

};

#endif