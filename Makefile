CC = g++
CFLAGS = -O2

a.out : app.o board.o
	$(CC) board.o app.o
app.o : app.cpp board.hpp
	$(CC) $(CFLAGS) -c app.cpp
board.o : board.cpp board.hpp
	$(CC) $(CFLAGS) -c board.cpp

