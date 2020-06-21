#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef SDTBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDDEF_H
#define STDDEF_H
#include <stddef.h>
#endif

#ifndef MAZE_H
#define MAZE_H
#include "maze.h"
#endif

#ifndef TILE_DEAFULT_H
#define TILE_DEAFULT_H
#include "tile_default.h"
#endif

#ifndef TILE_H
#define TILE_H
#include "tile.h"
#endif

#ifndef PRINTER_H
#define PRINTER_H
#include "printer.h"
#endif

void init_test_maze_1(maze_t* maze){
    init_maze(5, 4, maze);
    set_size_of_extra(sizeof(bool), maze);
    cell_t c;
    bool* extra;

    c = get_cell(maze, 0, 0);
    c.east  = false;
    c.start = true;
    set_cell(c, 0, 0, maze);
    extra = get_extra(maze, 0, 0);
    extra[0] = true;

    c = get_cell(maze, 1, 0);
    c.south  = false;
    set_cell(c, 1, 0, maze);
    extra = get_extra(maze, 1, 0);
    extra[0] = true;

    c = get_cell(maze, 2, 0);
    c.east  = false;
    c.south = false;
    c.west  = false;
    set_cell(c, 2, 0, maze);
    extra = get_extra(maze, 2, 0);
    extra[0] = true;

    c = get_cell(maze, 3, 0);
    c.south  = false;
    set_cell(c, 3, 0, maze);

    c = get_cell(maze, 4, 0);
    c.south = false;
    set_cell(c, 4, 0, maze);


    c = get_cell(maze, 0, 1);
    c.east  = false;
    c.south = false;
    set_cell(c, 0, 1, maze);
    extra = get_extra(maze, 0, 1);
    extra[0] = true;

    extra = get_extra(maze, 1, 1);
    extra[0] = true;

    c = get_cell(maze, 3, 1);
    c.south  = false;
    set_cell(c, 3, 1, maze);

    c = get_cell(maze, 2, 1);
    c.east  = false;
    set_cell(c, 2, 1, maze);
    extra = get_extra(maze, 2, 1);
    extra[0] = true;

    c = get_cell(maze, 4, 1);
    c.south = false;
    c.west  = false;
    set_cell(c, 4, 1, maze);


    c = get_cell(maze, 0, 2);
    c.east  = false;
    c.south = false;
    set_cell(c, 0, 2, maze);

    c = get_cell(maze, 1, 2);
    c.south  = false;
    set_cell(c, 1, 2, maze);

    c = get_cell(maze, 2, 2);
    c.east  = false;
    c.south = false;
    set_cell(c, 2, 2, maze);


    extra = get_extra(maze, 0, 3);
    extra[0] = true;

    c = get_cell(maze, 2, 3);
    c.east  = false;
    c.west  = false;
    set_cell(c, 2, 3, maze);

    c = get_cell(maze, 4, 3);
    c.west  = false;
    c.end = true;
    set_cell(c, 4, 3, maze);
}

int main(int argc, char* argv[]){

    //Initializing test maze
    maze_t myMaze;
    maze_t *pmyMaze = &myMaze;
    init_test_maze_1(pmyMaze);

    //Initializing tile set
    tile_set_t myTileSet;
    tile_set_t *pmyTileSet = &myTileSet;
    myTileSet = hedge_set;

    //Testing my print function
    print(pmyMaze, pmyTileSet , stdout);

    return 0;
}
