#ifndef MAZE_H
#define MAZE_H
#include <maze.h>
#endif

/**
 is
     replace the extra data in a maze with a working solution if one is possible and shorter than the max value of a long
 require
     maze must be valid and should be solvable
 notes
     (width*height) memory usage
     (width*height)^2 worst case time usage,
     if the shortest path is > the max value of a long, it will not find the solusion
*/
void solve_maze(maze_t *maze);
