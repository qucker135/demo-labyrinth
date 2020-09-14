CC = g++
EXE = main

all: main.cpp
	$(CC) main.cpp -o $(EXE)
	
run: 
	./$(EXE)
