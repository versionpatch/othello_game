CC = g++
CFLAGS = -O2

a.out : app.o board.o minmax.o
	$(CC) board.o minmax.o app.o
app.o : app.cpp board.hpp
	$(CC) $(CFLAGS) -c app.cpp
minmax.o : minmax.cpp minmax.hpp board.hpp
	$(CC) $(CFLAGS) -c minmax.cpp
board.o : board.cpp board.hpp
	$(CC) $(CFLAGS) -c board.cpp

