
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
    int column;
    int row;
};

int run_set_current_size = 0;

// Initialize a "run" set
struct CELL_COORDINATES* initialize_run_set(int maze_width) {

    struct CELL_COORDINATES *run_set = (struct CELL_COORDINATES*)calloc(maze_width, sizeof(struct CELL_COORDINATES));

    return run_set;
}

// Add a cell to the "run" set and randomly decide whether to go east or not
bool add_to_run_set(struct CELL_COORDINATES *run_set, struct CELL_COORDINATES *cell_to_be_added) {

    int i;

    //printf("Run set current size: %d\n", run_set_current_size);

    //printf("Adding to run set [%d,%d]...\n", (*cell_to_be_added).column, (*cell_to_be_added).row);

    if (run_set_current_size == 0) {
        // add to run set
        *run_set = *cell_to_be_added;

    } else {
        i = run_set_current_size;
        run_set[i] = *cell_to_be_added;
    }

    run_set_current_size++;

    // randomly decide whether to go east or not
    bool go_east = rand() & 1;

    for (int i = 0; i < run_set_current_size; i++) {
        //printf("Member %d of run_set is [column, row]: [%d, %d]\n", i, run_set[i].column, run_set[i].row);
    }

    return go_east;
}

// Empty the "run" set
void reinitialize_run_set(struct CELL_COORDINATES *run_set, int maze_width) {

    //free(run_set);

    if  (run_set != NULL) {
        free(run_set);
        run_set = NULL;
    }

    run_set = (struct CELL_COORDINATES*)calloc(maze_width, sizeof(struct CELL_COORDINATES));
    run_set_current_size = 0;

}

void repeated_procedures(struct CELL_COORDINATES run_set[], struct CELL_COORDINATES *current_cell_coordinates, maze_t* maze) {

    //printf("Current cell is [column, row] [%d,%d] of the maze...\n", (*current_cell_coordinates).column, (*current_cell_coordinates).row);

    if (((*current_cell_coordinates).row == (maze->end_y)) && ((*current_cell_coordinates).column == (maze->end_x))) {
        //printf("We reached the end of the maze. Exiting the function\n");
        return;
    }

    bool go_east = add_to_run_set(run_set, current_cell_coordinates);
    //cell_t new_cell;
    cell_t cell;
    int random_number;

    cell = get_cell(maze, (*current_cell_coordinates).column, (*current_cell_coordinates).row);

    if (go_east) {
        //printf("Will go EAST\n");
        // carve your way east
        cell.east = 0;

        if ((*current_cell_coordinates).column == (maze->width - 1)) {
            (*current_cell_coordinates).row++;
            (*current_cell_coordinates).column = 0;
            reinitialize_run_set(run_set, maze->width);
        } else {
            set_cell(cell, (*current_cell_coordinates).column, (*current_cell_coordinates).row, maze);
            // new cell is now the current cell
            (*current_cell_coordinates).column++;
        }

        // Recursion
        repeated_procedures(run_set, current_cell_coordinates, maze);
    } else {
        //printf("Will NOT go EAST\n");

        // randomly choose a cell from the "run" set
        random_number = rand() % run_set_current_size;

        //printf("Carving the member number %d of the run set...\n", random_number);

        struct CELL_COORDINATES random_cell_coordinates = run_set[random_number];

        cell_t random_cell = get_cell(maze, random_cell_coordinates.column, random_cell_coordinates.row);

        // carve North
        random_cell.north = 0;
        set_cell(random_cell, random_cell_coordinates.column, random_cell_coordinates.row, maze);

        //printf("Carved NORTH from the cell [column, row] [%d,%d] of the maze...\n", random_cell_coordinates.column, random_cell_coordinates.row);

        // empty "run" set
        reinitialize_run_set(run_set, maze->width);

        if ((*current_cell_coordinates).column == (maze->width - 1)) {
            (*current_cell_coordinates).row++;
            (*current_cell_coordinates).column = 0;
        } else {
            // new cell is now the current cell
            (*current_cell_coordinates).column++;
        }

        // Recursion
        repeated_procedures(run_set, current_cell_coordinates, maze);
    }

}

// Generates a maze based on the Sidewinder algorithm
void gen_sidewinder(maze_t* maze) {

    srand((unsigned)time(NULL));

    // start at 0,0
    struct CELL_COORDINATES *current_cell_coordinates = (struct CELL_COORDINATES*)malloc(sizeof(struct CELL_COORDINATES));
    (*current_cell_coordinates).row = 0;
    (*current_cell_coordinates).column = 0;

    // clear entire 1st row (i.e. set cell_t.east to 0 for each cell in that row)
    cell_t cell;
    for (int i = 0; i < maze->width; i++) {
        cell = get_cell(maze, i, (*current_cell_coordinates).row);
        cell.east = 0;
        set_cell(cell, i, (*current_cell_coordinates).row, maze);
    }

    // move on to next row
    (*current_cell_coordinates).row++;

    // initialize a "run" set to empty
    struct CELL_COORDINATES *run_set = initialize_run_set(maze->width);

    repeated_procedures(run_set, current_cell_coordinates, maze);
}
