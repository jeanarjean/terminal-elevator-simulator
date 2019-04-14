#ifndef MEDIATOR_H
#define MEDIATOR_H

class Elevator;

class Mediator
{
  public:
    Mediator();
    void start();
    ~Mediator();

  private:
    Elevator *elevator;
};

#endif