CC = g++
EXE = main

all: main.cpp
	$(CC) -lncurses main.cpp -o $(EXE)
	
run: 
	./$(EXE)
