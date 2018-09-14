EXE=Tetris
OBJECTS= threads.o main.o tetris.o
CC=gcc
FLAGS=-I./ -O3 -lrt -pthread

$(EXE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXE)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
