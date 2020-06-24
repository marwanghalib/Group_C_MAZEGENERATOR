#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef MAZE_H
#define MAZE_H
#include "maze.h"
#endif

#ifndef TILE_H
#define TILE_H
#include "tile.h"
#endif

/**
This function will take in a maze object, look at it's file pointer that contains 
a text file with a maze, and populate the maze object data.

After running parser, you can now take this maze object and pass it to the printer to get printed.
*/

void parse_maze(maze_t *my_maze);