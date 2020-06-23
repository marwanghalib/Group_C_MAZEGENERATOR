CC = gcc

#Add debug info, all warnings, and all extra warnings
CFLAGS = -g -Wall -Wextra -I ./src -I ./test

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
test_build_folder := $(shell mkdir -p test/build)

default: cmaze

clean:
	rm -rf bin/* build/* test/build/*

cmaze: coll_input.o main.o maze.o printer.o tile.o tile_default.o backtrack.o sidewinder.o backtrack.o sidewinder.o solve.o
	$(CC) $(CFLAGS) build/* -o bin/cmaze

test: cmaze test_maze.o test_tile.o test_tile_default.o test_solver.o
	$(CC) $(CFLAGS) test/build/test_maze.o         build/maze.o         -o bin/test_maze
	$(CC) $(CFLAGS) test/build/test_tile.o         build/tile.o         -o bin/test_tile
	$(CC) $(CFLAGS) test/build/test_tile_default.o build/tile_default.o -o bin/test_tile_default
	$(CC) $(CFLAGS) test/build/test_solver.o  build/maze.o  build/tile.o  build/tile_default.o  build/backtrack.o build/solve.o build/sidewinder.o build/printer.o -o bin/test_solver
	bash -c "bin/test_maze; bin/test_tile; bin/test_tile_default; bin/test_solver;"


#src
backtrack.o:
	$(CC) $(CFLAGS) -c src/backtrack.c -o build/backtrack.o

coll_input.o:
	$(CC) $(CFLAGS) -c src/coll_input.c -o build/coll_input.o

main.o:
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

maze.o:
	$(CC) $(CFLAGS) -c src/maze.c -o build/maze.o

printer.o:
	$(CC) $(CFLAGS) -c src/printer.c -o build/printer.o

sidewinder.o:
	$(CC) $(CFLAGS) -c src/sidewinder.c -o build/sidewinder.o

tile.o:
	$(CC) $(CFLAGS) -c src/tile.c -o build/tile.o

tile_default.o:
	$(CC) $(CFLAGS) -c src/tile_default.c -o build/tile_default.o

solve.o:
	$(CC) $(CFLAGS) -c src/solve.c -o build/solve.o
#test
test_maze.o:
	$(CC) $(CFLAGS) -c test/test_maze.c -o test/build/test_maze.o

test_tile.o:
	$(CC) $(CFLAGS) -c test/test_tile.c -o test/build/test_tile.o

test_tile_default.o:
	$(CC) $(CFLAGS) -c test/test_tile_default.c -o test/build/test_tile_default.o


test_solver.o:
	$(CC) $(CFLAGS) -c test/test_solver.c -o test/build/test_solver.o




