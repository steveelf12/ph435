CFLAGS=-Wall	-g
all:	simulate
simulate: simulate.cpp
	g++ simulate.cpp -o simulate -lm
clean:
	rm	-f	ex1
