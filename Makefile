# This is just a simple Makefile to make compilation less of a hassle
# and should be improved later

CC	=	g++
EXE	=	ON
SRC	=	./*.cpp
STD	=	-std=c++11
LIB	=	-lSDL2

default: clean on

on:
	$(CC) -o $(EXE) $(SRC) $(STD) $(LIB)

clean:
	rm -f $(EXE)
