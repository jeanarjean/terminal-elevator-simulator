CFLAGS = -O
CC = g++
SRC = Main.cpp Elevator.cpp Mediator.cpp
OBJ = $(SRC:.cpp = .o)
Elevator: $(OBJ)
	$(CC) $(CFLAGS) -o terminal-elevator-simulator $(OBJ) -lncurses
clean:
	rm -f core *.o 
