CC = g++
CFLAGS  = -g -Wall -std=c++11 -pedantic

all: saturday

saturday: main.cpp formula.cpp parser.cpp clause.cpp literal.cpp model.cpp
	$(CC) $(CFLAGS) -o saturday main.cpp

clean:
	rm saturday
