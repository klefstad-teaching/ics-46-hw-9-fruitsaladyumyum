CXX = g++

CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: dijkstras_main ladder_main

dijkstras_main: ./src/dijkstras_main.cpp lib/dijkstras.o
	$(CXX) ./src/dijkstras_main.cpp lib/dijkstras.o -o dijkstras_main $(CXXFLAGS)

lib/dijkstras.o: ./src/dijkstras.h ./src/dijkstras.cpp
	$(CXX) -c ./src/dijkstras.cpp -o lib/dijkstras.o $(CXXFLAGS)

ladder_main: ./src/ladder_main.cpp lib/ladder.o
	$(CXX) ./src/ladder_main.cpp lib/ladder.o -o ladder_main $(CXXFLAGS)

lib/ladder.o: ./src/ladder.h ./src/ladder.cpp
	$(CXX) -c ./src/ladder.cpp -o lib/ladder.o $(CXXFLAGS)

clean:
	/bin/rm dijkstras_main ladder_main