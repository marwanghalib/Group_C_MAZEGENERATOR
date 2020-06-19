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

// Used for adding and keeping track of cells in the "run" set
struct CELL_COORDINATES
{
    int x;
    int y;
};

// Initialize a "run" set
struct CELL_COORDINATES* initialize_run_set(int maze_width) {

    struct CELL_COORDINATES *run_set = (struct CELL_COORDINATES*)calloc(maze_width, sizeof(struct CELL_COORDINATES));

    return run_set;
}

// Add a cell to the "run" set and randomly decide whether to go east or not
bool add_to_run_set(struct CELL_COORDINATES *run_set, int x, int y) {

    struct CELL_COORDINATES cell_to_be_added;
    cell_to_be_added.x = x;
    cell_to_be_added.y = y;

    // add to run set
    run_set = &cell_to_be_added;
    run_set++;

    // randomly decide whether to go east or not
    bool go_east = rand() & 1;

    return go_east;
}

// Empty the "run" set
void clear_run_set(struct CELL_COORDINATES *run_set) {

    free(run_set);

}

void repeated_procedures(struct CELL_COORDINATES run_set[], int current_column, int current_row, maze_t* maze) {

    bool go_east = add_to_run_set(run_set, current_column, current_row);
    cell_t new_cell;
    cell_t cell;
    int random_number;

    cell = get_cell(maze, current_column, current_row);



    if (go_east) {
        // carve your way east
        cell.east = 0;

        // new cell is now the current cell
        current_column++;
        new_cell = get_cell(maze, current_column, current_row);


        // CHECK FOR SOMETHING BEFORE YOU REPEATING THE ABOVE PROCEDURES

        // Recursion?, can we do realloc??
        repeated_procedures(run_set, current_column, current_row, maze);

    } else {
        // randomly choose a cell from the "run" set
        random_number = rand() % maze->width;
        struct CELL_COORDINATES random_cell_coordinates = run_set[random_number];

        cell_t random_cell = get_cell(maze, random_cell_coordinates.x, random_cell_coordinates.y);

        // carve North
        random_cell.north = 0;

        // empty "run" set
        clear_run_set(run_set);

        // set next cell in row to current cell

        // CHECK FOR SOMETHING BEFORE YOU REPEATING THE ABOVE PROCEDURES

        // Recursion?, can we do realloc??
        repeated_procedures(run_set, current_column, current_row, maze);
    }

}

// Generates a maze based on the Sidewinder algorithm
void gen_sidewinder(maze_t* maze) {

    srand((unsigned)time(NULL));

    // start at 0,0
    int current_row = 0;
    int current_column = 0;

    cell_t new_cell;

    // clear entire 1st row (i.e. set cell_t.east to 0 for each cell in that row)
    cell_t cell;
    for (int i = 0; i < maze->width; i++) {
        cell = get_cell(maze, i, current_row);
        cell.east = 0;
        set_cell(cell, i, current_row, maze);
    }

    // move on to next row
    current_row++;

    // initialize a "run" set to empty
    struct CELL_COORDINATES *run_set = initialize_run_set(maze->width);

    repeated_procedures(run_set, current_column, current_row, maze);

}

// -----------------------------------------------------------------------

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
