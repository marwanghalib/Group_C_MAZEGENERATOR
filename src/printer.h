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

void print_maze(maze_t *myMaze, const tile_set_t *myTileSet , FILE* destination);
