CC = gcc

#Add debug info, all warnings, and all extra warnings
CFLAGS = -g -Wall -Wextra -I ./src -I ./test

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)

default: cmaze


#cmaze:
#	echo "test"



cmaze: main.o maze.o tile.o
	$(CC) $(CFLAGS) build/main.o build/maze.o -o bin/cmaze

main.o:
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

test: cmaze test_main.o test_maze.o test_tile.o test_tile_default.o
	$(CC) $(CFLAGS) build/test_main.o -o bin/test_main
	$(CC) $(CFLAGS) build/test_maze.o build/maze.o -o bin/test_maze
	$(CC) $(CFLAGS) build/test_tile.o build/tile.o -o bin/test_tile
	$(CC) $(CFLAGS) build/test_tile_default.o build/tile.o -o bin/test_tile_default
	bash -c "bin/test_maze; bin/test_tile; bin/test_tile_default;"

test_main.o:
	 $(CC) $(CFLAGS) -c test/test_main.c -o build/test_main.o

maze.o:
	$(CC) $(CFLAGS) -c src/maze.c -o build/maze.o

tile.o:
	$(CC) $(CFLAGS) -c src/tile.c -o build/tile.o

test_maze.o: maze.o
	$(CC) $(CFLAGS) -c test/test_maze.c -o build/test_maze.o
	
test_tile.o: tile.o
	$(CC) $(CFLAGS) -c test/test_tile.c -o build/test_tile.o

test_tile_default.o: tile.o
	$(CC) $(CFLAGS) -c test/test_tile_default.c -o build/test_tile_default.o

#CLEAN COMMANDS
clean:
	rm -rf bin/* build/*

