#ifndef FLOOR_H
#define FLOOR_H

class Floor
{
    public: 
    Floor(int height);

    void Tick();
    void PressUpButton();
    void PressDownButton();
    void ResetUpButton();
    void ResetDownButton();
    int GetHeight();
    bool UpButtonPressed();
    bool DownButtonPressed();

    private:
    bool upButtonPresed;
    bool downButtonPresed;
    int height;

    void InitRender();
};

#endif