CC := g++
CXXFLAGS := -Wall -Werror
SRC := ./src/*.cpp
EXE := main

$(EXE): $(EXE).cpp
	$(CC) $(CXXFLAGS) $(EXE).cpp $(SRC) -o $(EXE)
