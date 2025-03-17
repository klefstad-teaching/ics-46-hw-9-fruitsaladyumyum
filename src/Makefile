CXX = g++

CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: ds_main ladder_main

ds_main: dijkstras_main.cpp ../lib/dijkstras.o
	$(CXX) dijkstras_main.cpp ../lib/dijkstras.o -o ds_main $(CXXFLAGS)

../lib/dijkstras.o: dijkstras.h dijkstras.cpp
	$(CXX) -c dijkstras.cpp -o ../lib/dijkstras.o $(CXXFLAGS)

ladder_main: ladder_main.cpp ../lib/ladder.o
	$(CXX) ladder_main.cpp ../lib/ladder.o -o ladder_main $(CXXFLAGS)

../lib/ladder.o: ladder.h ladder.cpp
	$(CXX) -c ladder.cpp -o ../lib/ladder.o $(CXXFLAGS)

clean:
	/bin/rm dijkstras_main ladder_main