 
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


/** @brief Used for adding and keeping track of cells in the "run" set
 */
struct CELL_COORDINATES
{
    int column;
    int row;
};

int run_set_current_size = 0; // keeps track of the size of a "run" set
bool run_set_has_north_path = 0; // at the end of of a maze row we need this to figure out whether the last "run" set of the row has a path NORTH


/** @brief Initialize a "run" set
 *  param int
 *  return CELL_COORDINATE
 */
struct CELL_COORDINATES* initialize_run_set(int maze_width) {

    struct CELL_COORDINATES *run_set = (struct CELL_COORDINATES*)calloc(maze_width, sizeof(struct CELL_COORDINATES));

    return run_set;
}


/** @brief Add a cell to the "run" set and randomly decide whether to go east or not
 *  @param CELL_COORDINATES*
 *  @param CELL_COORDINATES*
 *  return bool
*/
bool add_to_run_set(struct CELL_COORDINATES *run_set, struct CELL_COORDINATES *cell_to_be_added) {

    int i;

    if (run_set_current_size == 0) {
        // add to beginning of the "run" set
        *run_set = *cell_to_be_added;

    } else {
        // append to the "run" set
        i = run_set_current_size;
        run_set[i] = *cell_to_be_added;
    }

    // we added a cell to the "run" set, increase the size counter
    run_set_current_size++;

    // randomly decide whether to go east or not
    bool go_east = rand() & 1;

    return go_east;
}


/** @brief Empty the "run" set
 *  return void
 */
void reinitialize_run_set() {
    // set the counter of size to 0
    run_set_current_size = 0;
}




/** @brief end_of_run_set
 *  @param cell_t*
 *  @param int
 *  @param CELL_COORDINATES
 *  @param CELL_COORDINATES*
 *  @param maze_t*
 *  return void
*/
void end_of_run_set(cell_t *cell, int *random_number, struct CELL_COORDINATES run_set[], struct CELL_COORDINATES *current_cell_coordinates, maze_t* maze) {

    // go through the "run" set and make check if there is a path NORTH from any of its members
    for (int i = 0; i < run_set_current_size; i++) {
        *cell = get_cell(maze, (*current_cell_coordinates).column, (*current_cell_coordinates).row);
        if (!((*cell).north)) {
            // we found a path NORTH from this "run" set
            run_set_has_north_path = 1;
        }
    }

    // we did not find a path NORTH from this "run" set
    if (!run_set_has_north_path) {
        // pick a random member of the "run" set and carve NORTH
        // randomly choose a cell from the "run" set
        *random_number = rand() % run_set_current_size;

        struct CELL_COORDINATES random_cell_coordinates = run_set[*random_number];
        cell_t random_cell = get_cell(maze, random_cell_coordinates.column, random_cell_coordinates.row);

        // carve North
        random_cell.north = 0;
        set_cell(random_cell, random_cell_coordinates.column, random_cell_coordinates.row, maze);
    }
}

//

/** @brief carves the passage to create "run" sets
 *  @param CELL_COORDINATES
 *  @param CELL_COORDINATES*
 *  @param maze_t*
 *  return void
*/
void carve_passage(struct CELL_COORDINATES run_set[], struct CELL_COORDINATES *current_cell_coordinates, maze_t* maze) {

    cell_t cell;
    int random_number;

    // add cell to the "run" set and decide randomly whether or not to carve EAST
    bool go_east = add_to_run_set(run_set, current_cell_coordinates);

    // Check if you're at the end of the maze first
    if (((*current_cell_coordinates).row == (maze->end_y)) && ((*current_cell_coordinates).column == (maze->end_x))) {

        // make sure there is a way NORTH for the last "run" set
        end_of_run_set(&cell, &random_number, run_set, current_cell_coordinates, maze);

        // you have now generated a maze
        return;
    }

    cell = get_cell(maze, (*current_cell_coordinates).column, (*current_cell_coordinates).row);

    if (go_east) {
        // carve your way east
        cell.east = 0;

        if ((*current_cell_coordinates).column == (maze->width - 1)) {
            // we are at the end of the row

            // make sure there is a way NORTH for the last "run" set
            end_of_run_set(&cell, &random_number, run_set, current_cell_coordinates, maze);

            // move on to the next row starting at the first column
            (*current_cell_coordinates).row++;
            (*current_cell_coordinates).column = 0;

            // now we can reinitialize the "run" set
            reinitialize_run_set();

        } else {
            set_cell(cell, (*current_cell_coordinates).column, (*current_cell_coordinates).row, maze);
            // new cell is now the current cell
            (*current_cell_coordinates).column++;
        }

        // Continuing carving your passage
        carve_passage(run_set, current_cell_coordinates, maze);

    } else {
        // randomly choose a cell from the "run" set
        random_number = rand() % run_set_current_size;

        struct CELL_COORDINATES random_cell_coordinates = run_set[random_number];

        cell_t random_cell = get_cell(maze, random_cell_coordinates.column, random_cell_coordinates.row);

        // carve North
        random_cell.north = 0;
        set_cell(random_cell, random_cell_coordinates.column, random_cell_coordinates.row, maze);

        // empty "run" set
        reinitialize_run_set();

        if ((*current_cell_coordinates).column == (maze->width - 1)) {
            // move on to the next row starting at the first column
            (*current_cell_coordinates).row++;
            (*current_cell_coordinates).column = 0;
        } else {
            // new cell is now the current cell
            (*current_cell_coordinates).column++;
        }

        // Continuing carving your passage
        carve_passage(run_set, current_cell_coordinates, maze);
    }

}


/** @brief Generates a maze based on the Sidewinder algorithm
 *  @param maze_t*
 *  return void
*/
void gen_sidewinder(maze_t* maze) {

    // enables random number generation
    srand((unsigned)time(NULL));

    // start at the specified maze object starting coordinates
    struct CELL_COORDINATES *current_cell_coordinates = (struct CELL_COORDINATES*)malloc(sizeof(struct CELL_COORDINATES));
    (*current_cell_coordinates).row = maze->start_y;
    (*current_cell_coordinates).column = maze->start_x;

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

    // carve your passage
    carve_passage(run_set, current_cell_coordinates, maze);

    // free the memory allocated for storing the coordinates of the cell we are manipulating at a specific moment 
    if  (current_cell_coordinates != NULL) {
        free(current_cell_coordinates);
        current_cell_coordinates = NULL;
    }

    // free the memory allocated for storing the "run" set
    if  (run_set != NULL) {
        free(run_set);
        run_set = NULL;
    }
}
