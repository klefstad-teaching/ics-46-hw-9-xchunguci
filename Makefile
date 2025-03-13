CXX = g++
CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: dij_main lad_main

dij_main: dijkstras.o src/dijkstras_main.cpp
	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp dijkstras.o -o dij_main

dijkstras.o: src/dijkstras.cpp src/dijkstras.h
	$(CXX) $(CXXFLAGS) -c src/dijkstras.cpp -o dijkstras.o

lad_main: ladder.o src/ladder_main.cpp
	$(CXX) $(CXXFLAGS) src/ladder_main.cpp ladder.o -o lad_main

ladder.o: src/ladder.cpp src/ladder.h
	$(CXX) $(CXXFLAGS) -c src/ladder.cpp -o ladder.o

clean:
	rm -f dij_main lad_main dijkstras.o ladder.o