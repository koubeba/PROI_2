ship: interface.o board.o ship.o test.o
	g++ -w -o ship interface.o board.o ship.o test.o

interface.o: ship.h board.h interface.h ship.cpp board.cpp interface.cpp
	g++ -w -c interface.cpp board.cpp ship.cpp

board.o: ship.h board.h ship.cpp board.cpp
	g++ -w -c board.cpp ship.cpp

ship.o: ship.h ship.cpp
	g++ -w -c ship.cpp
