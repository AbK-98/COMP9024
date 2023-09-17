CC      = gcc
CFLAGS  = -Wall -Werror -std=c11

.PHONY : clean

graphAnalyser : graphAnalyser.o Graph.o
	$(CC) $(CFLAGS) -o $@ graphAnalyser.o Graph.o

graphAnalyser.o : graphAnalyser.c Graph.h
	$(CC) $(CFLAGS) -c graphAnalyser.c

Graph.o : Graph.c Graph.h
	$(CC) $(CFLAGS) -c Graph.c

clean : 
	rm -f -- *.o graphAnalyser