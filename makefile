OBJS = exerciseJournal.o dstring.o main.o helper.o
SRCS = exerciseJournal.cpp dstring.cpp main.cpp helper.cpp
CC = g++
DEBUG = -g
CXXFLAGS = -std=c++14 -Wall -Iinclude $(DEBUG)
LFLAGS = -Wall $(DEBUG)
PROGRAM = project5

project1: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(PROGRAM)

all: $(OBJS)
	$(CC) $(CXXFLAGS) $(SRCS)

clean:
	-rm $(OBJS) $(PROGRAM)

tar:
	tar czvf $(PROGRAM).tar.gz makefile ./include/*.h $(SRCS) exercise.txt

doxygen:
	doxygen $(PROGRAM).doxygen.config
