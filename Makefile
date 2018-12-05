CFLAGS = -O
CC = g++
SRC = Main.cpp Elevator.cpp
OBJ = $(SRC:.cpp = .o)
Elevator: $(OBJ)
	$(CC) $(CFLAGS) -o Elevator $(OBJ)
clean:
	rm -f core *.o 
