CFLAGS = -O
CC = g++
SRC = Main.cpp Elevator.cpp Mediator.cpp
OBJ = $(SRC:.cpp = .o)
Elevator: $(OBJ)
	$(CC) $(CFLAGS) -o Terminal-Elevator-Simulator $(OBJ) -lncurses
clean:
	rm -f core *.o 
