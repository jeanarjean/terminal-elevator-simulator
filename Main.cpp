#include "Mediator.h"
#include <ncurses.h>

int main(int argc, char const *argv[])
{
    initscr();
    noecho();

    Mediator mediator;
    mediator.Run();

    endwin();
    return 0;
}
