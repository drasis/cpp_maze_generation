PROG = maze-maker
CC = g++
CPPFLAGS = -g
OBJS = randomHelpers.o cell.o grid.o mask.o maze.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
	rm *.o
maze.o :
	$(CC) $(CPPFLAGS) -c maze.cpp
mask.o : mask.h
	$(CC) $(CPPFLAGS) -c mask.cpp
grid.o : grid.h
	$(CC) $(CPPFLAGS) -c grid.cpp
cell.o : cell.h
	$(CC) $(CPPFLAGS) -c cell.cpp
randomHelpers.o : randomHelpers.h
	$(CC) $(CPPFLAGS) -c randomHelpers.cpp
clean:
	rm -f core $(PROG) $(OBJS)