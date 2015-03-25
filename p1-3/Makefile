#
#	Makefile for mscp
#
CC=g++
CFLAGS=-Wall -g3 -ansi -pedantic 

TARGET=mscp
SOURCE=mscp.cpp board.cpp

mscp:	board.o mscp.o
	$(CC) $(CFLAGS) board.o mscp.o -o $(TARGET) 
	
	
board.o:	board.cpp board.h
	$(CC) $(CFLAGS) -c board.cpp

mscp.o:	mscp.cpp board.h
	$(CC) $(CFLAGS) -c mscp.cpp

clean:
	rm -f $(TARGET) *.o

