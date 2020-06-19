#ifndef MAZE_H
#define MAZE_H
#include "maze.h"
#endif

#ifndef PRINTER_H
#define PRINTER_H
#include "printer.h"
#endif

#ifndef TILE_H
#define tile_H
#include "tile.h"
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

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

void gen_sidewinder(maze_t* maze) {

    int current_row = 0;

    // clear entire 1st row (i.e. set cell_t.east to 0)
    cell_t cell;
    for (int i = 0; i < maze->width; i++) {
        cell = get_cell(maze, i, current_row);
        cell.east = 0;
        set_cell(cell, i, current_row, maze);
    }

    // move on to next row
    current_row++;

    // initializ a "run" set to empty
    cell_t run_set[maze->width];

    // add current cell to "run" set
    cell = get_cell(maze, 0, current_row);
    run_set[0] = cell;

    // randomly decide whether to go east or not
    srand((unsigned)time(NULL));
    bool go_east = rand() & 1;

    // if you decided to go east
    if (go_east) {
        // new cell is now the current cell


    } else {

    }


}


int main()
{
    // initialize a maze for testing
    int width = 10;
    int height = 5;
    maze_t maze;
    init_maze(width, height, &maze);

    // Generate a maze using the Sidewinder algorithm
    gen_sidewinder(&maze);

    // Open a file to print the maze in
    FILE *fptr;
    fptr = fopen("output.txt", "w");

    //Choose the tileset character
    tile_set_t* tile_set = new_tile_set("*");

    // Print the maze in the file
    print(&maze, tile_set, fptr);

    // Close the file
    fclose(fptr);

    return 0;
}
