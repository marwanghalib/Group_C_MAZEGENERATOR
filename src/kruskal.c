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

#define NORTH 1
#define SOUTH 2
#define EAST 4
#define WEST 8



// Used for adding and keeping track of cells in the "run" set
struct CELL_COORDINATES
{
    int column;
    int row;
};

// Used for adding and keeping track of cells in the "run" set
struct TREE
{
    struct CELL_COORDINATES start_edge;
    struct CELL_COORDINATES end_edge;
    int size : 1;
    struct CELL_COORDINATES members[];
};

int tree_set_current_size = 0;
int counter = 3;

// Initialize a tree set
struct TREE* initialize_tree_set() {

    struct TREE *tree_set = (struct TREE*)malloc(sizeof(struct TREE));

    return tree_set;
}

void add_to_tree_set(struct TREE *tree_set, struct TREE *tree_to_be_added) {

    int i;

    if (tree_set_current_size == 0) {
        // add to beginning of the "run" set
        *tree_set = *tree_to_be_added;

    } else {
        // append to the "run" set
        i = tree_set_current_size;
        tree_set[i] = *tree_to_be_added;
    }

    // we added a cell to the "run" set, increase the size counter
    tree_set_current_size++;
}

int move_x(int direction) {
    int moved_x;
    switch (direction) {
    case NORTH :
        moved_x = 0;
        break;
    case SOUTH :
        moved_x = 0;
        break;
    case EAST :
        moved_x = 1;
        break;
    case WEST :
        moved_x = -1;
        break;
    }
    return moved_x;
}

int move_y(int direction) {
    int moved_y;
    switch (direction) {
    case NORTH :
        moved_y = 1;
        break;
    case SOUTH :
        moved_y = -1;
        break;
    case EAST :
        moved_y = 0;
        break;
    case WEST :
        moved_y = 0;
        break;
    }
    return moved_y;
}

void carve_cell(maze_t* maze, struct CELL_COORDINATES cell_coordinates, int direction_to_carve) {
    cell_t cell = get_cell(maze, cell_coordinates.column, cell_coordinates.row);

    switch (direction_to_carve) {
    case NORTH :
        cell.north = 0;
        break;
    case SOUTH :
        cell.south = 0;
        break;
    case EAST :
        cell.east = 0;
        break;
    case WEST :
        cell.west = 0;
        break;
    }

    set_cell(cell, cell_coordinates.column, cell_coordinates.row, maze);

}

int direction_from_neighbour_to_current_cell(struct CELL_COORDINATES neighbour, struct CELL_COORDINATES current_cell) {

    int neighbour_x = neighbour.column;
    int neighbour_y = neighbour.row;
    int current_x = current_cell.column;
    int current_y = current_cell.row;


    int difference_x = neighbour_x - current_x;
    int difference_y = neighbour_y - current_y;

    if (difference_y == 0 && difference_x == 1) {
        return EAST;
    } else if (difference_y == 0 && difference_x == -1) {
        return WEST;
    } else if (difference_y == 1 && difference_x == 0) {
        return SOUTH;
    } else if (difference_y == -1 && difference_x == 0) {
        return NORTH;
    } else {
        return 0;
    }
}


void repeated_procedures(maze_t* maze, struct TREE *tree_set, int number_of_edges, struct CELL_COORDINATES cell_coordinates, struct CELL_COORDINATES *edges) {

    // select random edge
    int random_number_edges = rand() % number_of_edges;
    printf("Random number edges: %d\n", random_number_edges);
    cell_coordinates = edges[random_number_edges];
    printf("Random cell [column, row]: [%d,%d]\n", edges[random_number_edges].column, edges[random_number_edges].row);

    // pick a cell adjacent to add to set
    int directions[4] = {NORTH, SOUTH, EAST, WEST};
    int random_number_directions = rand() % 4;
    int direction_chosen = directions[random_number_directions];
    int moved_x = move_x(direction_chosen);
    int moved_y = move_y(direction_chosen);
    struct CELL_COORDINATES neighbour_chosen;
    neighbour_chosen.column = cell_coordinates.column + moved_x;
    neighbour_chosen.row = cell_coordinates.row + moved_y;

    printf("Neighbour cell [column, row]: [%d,%d]\n", neighbour_chosen.column, neighbour_chosen.row);

    // make sure neighbour is a cell in the maze
    if (neighbour_chosen.column < maze->width &&
            neighbour_chosen.column >= 0 &&
            neighbour_chosen.row >= 0 &&
            neighbour_chosen.row < maze->height) {


        // MAKE SURE YOU CARVE BETWEEN THE TWO CELLS
        // if i am carving from neighbour to cell_coordinates, I will carve..
        int direction_chosen_to_carve = direction_from_neighbour_to_current_cell(neighbour_chosen, cell_coordinates);

        // any path between the two cells?
        if (0) {

        } else {

        }




        char *direction_string;
        switch (direction_chosen_to_carve) {
        case NORTH :
            direction_string = "NORTH";
            break;
        case SOUTH :
            direction_string = "SOUTH";
            break;
        case EAST :
            direction_string = "EAST";
            break;
        case WEST :
            direction_string = "WEST";
            break;
        }




        printf("Will Carve %s from [%d, %d]\n", direction_string, cell_coordinates.column, cell_coordinates.row);

        carve_cell(maze, cell_coordinates, direction_chosen_to_carve);

        // remove edge from edges array
        for (int i = random_number_edges; i < number_of_edges; i++)
        {
            edges[i] = edges[i + 1];
        }

        /* Decrement number of edges counter size by 1 */
        number_of_edges--;


        struct TREE tree;
        tree.start_edge = cell_coordinates;
        tree.end_edge = neighbour_chosen;
        //tree.size++;
        add_to_tree_set(tree_set, &tree);

        // add edge to edges checked
        if (number_of_edges == 0) {
            printf("WILL RETURN\n");
            return;
        } else {

            // choose a new edge randomly
            repeated_procedures(maze, tree_set, number_of_edges, cell_coordinates, edges);
        }




    } else {
        // cell outside of maze, choose a different direction
        repeated_procedures(maze, tree_set, number_of_edges, cell_coordinates, edges);

    }




}

void connect_sets(maze_t* maze, struct TREE *tree_set) {

    //if (tree_set_current_size == 0) {
    //  return;
    //}

    int new_tree_set_size = 0;
    int direction_chosen_to_carve;
    struct TREE tree;
    bool adjacent;

    for (int f = 0; f < tree_set_current_size; f++) {
        for (int p = f + 1; p < tree_set_current_size ; p++) {

            /*
                        printf("Comparing tree %d with tree %d:  start_x %d, start_y %d, end_x %d, end_y %d | start_x %d, start_y %d, end_x %d, end_y %d \n",
                               f,
                               p,
                               (tree_set[f]).start_edge.row,
                               (tree_set[f]).start_edge.column,
                               (tree_set[f]).end_edge.row,
                               (tree_set[f]).end_edge.column,
                               (tree_set[p]).start_edge.row,
                               (tree_set[p]).start_edge.column,
                               (tree_set[p]).end_edge.row,
                               (tree_set[p]).end_edge.column);
                               */


            int x, y, x1, y1, x2, y2, x3, y3;
            adjacent = false;

            x = (tree_set[f]).end_edge.row;
            y = (tree_set[f]).end_edge.column;

            x1 = (tree_set[f]).start_edge.row;
            y1 = (tree_set[f]).start_edge.column;

            x2 = (tree_set[p]).start_edge.row;
            y2 = (tree_set[p]).start_edge.column;

            x3 = (tree_set[p]).end_edge.row;
            y3 = (tree_set[p]).end_edge.column;

            // are the trees adjacent?
            // compare end wih start of other then with end of other

            // compare f end with p start
            if ( (x > x2 ? x - x2 : x2 - x) == 0 ) {
                if ((y > y2 ? y - y2 : y2 - y) == 1) {
                    // adjacent, carve between
                    direction_chosen_to_carve = direction_from_neighbour_to_current_cell((tree_set[f]).end_edge, (tree_set[p]).start_edge);
                    carve_cell(maze, (tree_set[p]).start_edge, direction_chosen_to_carve);
                    tree.start_edge = (tree_set[f]).end_edge;
                    tree.end_edge = (tree_set[p]).start_edge;
                    tree_set[new_tree_set_size] = tree;
                    adjacent = true;
                    new_tree_set_size++;
                }
            } else if ((x > x2 ? x - x2 : x2 - x) == 1) {
                if ((y > y2 ? y - y2 : y2 - y) == 0) {
                    // adjacent, carve between
                    direction_chosen_to_carve = direction_from_neighbour_to_current_cell((tree_set[f]).end_edge, (tree_set[p]).start_edge);
                    carve_cell(maze, (tree_set[p]).start_edge, direction_chosen_to_carve);
                    tree.start_edge = (tree_set[f]).end_edge;
                    tree.end_edge = (tree_set[p]).start_edge;
                    tree_set[new_tree_set_size] = tree;
                    adjacent = true;
                    new_tree_set_size++;
                }


            }

            // compare f end with p end
            if ( !adjacent
                    && (x > x3 ? x - x3 : x3 - x) == 0 ) {
                if ((y > y3 ? y - y3 : y3 - y) == 1) {
                    // adjacent, carve between
                    direction_chosen_to_carve = direction_from_neighbour_to_current_cell((tree_set[f]).end_edge, (tree_set[p]).end_edge);
                    carve_cell(maze, (tree_set[p]).end_edge, direction_chosen_to_carve);
                    tree.start_edge = (tree_set[f]).end_edge;
                    tree.end_edge = (tree_set[p]).end_edge;
                    tree_set[new_tree_set_size] = tree;
                    adjacent = true;
                    new_tree_set_size++;

                }
            } else if ((x > x3 ? x - x3 : x3 - x) == 1) {
                if ((y > y3 ? y - y3 : y3 - y) == 0) {
                    // adjacent, carve between
                    direction_chosen_to_carve = direction_from_neighbour_to_current_cell((tree_set[f]).end_edge, (tree_set[p]).end_edge);
                    carve_cell(maze, (tree_set[p]).end_edge, direction_chosen_to_carve);

                    tree.start_edge = (tree_set[f]).end_edge;
                    tree.end_edge = (tree_set[p]).end_edge;
                    tree_set[new_tree_set_size] = tree;
                    adjacent = true;
                    new_tree_set_size++;
                }


            }


            // compare f start with p start
            if ( !adjacent
                    && (x1 > x2 ? x1 - x2 : x2 - x1) == 0 ) {
                if ((y1 > y2 ? y1 - y2 : y2 - y1) == 1) {
                    // adjacent, carve between
                    direction_chosen_to_carve = direction_from_neighbour_to_current_cell((tree_set[f]).start_edge, (tree_set[p]).start_edge);
                    carve_cell(maze, (tree_set[p]).start_edge, direction_chosen_to_carve);

                    tree.start_edge = (tree_set[f]).start_edge;
                    tree.end_edge = (tree_set[p]).start_edge;
                    tree_set[new_tree_set_size] = tree;
                    adjacent = true;
                    new_tree_set_size++;

                }
            } else if ((x1 > x2 ? x1 - x2 : x2 - x1) == 1) {
                if ((y1 > y2 ? y1 - y2 : y2 - y1) == 0) {
                    // adjacent, carve between
                    direction_chosen_to_carve = direction_from_neighbour_to_current_cell((tree_set[f]).start_edge, (tree_set[p]).start_edge);
                    carve_cell(maze, (tree_set[p]).start_edge, direction_chosen_to_carve);


                    tree.start_edge = (tree_set[f]).start_edge;
                    tree.end_edge = (tree_set[p]).start_edge;
                    tree_set[new_tree_set_size] = tree;
                    adjacent = true;
                    new_tree_set_size++;
                }


            }


            // compare f start with p end
            if ( !adjacent
                    && (x1 > x3 ? x1 - x3 : x3 - x1) == 0 ) {
                if ((y1 > y3 ? y1 - y3 : y3 - y1) == 1) {
                    // adjacent
                    direction_chosen_to_carve = direction_from_neighbour_to_current_cell((tree_set[f]).start_edge, (tree_set[p]).end_edge);
                    carve_cell(maze, (tree_set[p]).end_edge, direction_chosen_to_carve);


                    tree.start_edge = (tree_set[f]).start_edge;
                    tree.end_edge = (tree_set[p]).end_edge;
                    tree_set[new_tree_set_size] = tree;
                    adjacent = true;
                    new_tree_set_size++;


                }
            } else if ((x1 > x3 ? x1 - x3 : x3 - x1) == 1) {
                if ((y1 > y3 ? y1 - y3 : y3 - y1) == 0) {
                    // adjacent
                    direction_chosen_to_carve = direction_from_neighbour_to_current_cell((tree_set[f]).start_edge, (tree_set[p]).end_edge);
                    carve_cell(maze, (tree_set[p]).end_edge, direction_chosen_to_carve);


                    tree.start_edge = (tree_set[f]).start_edge;
                    tree.end_edge = (tree_set[p]).end_edge;
                    tree_set[new_tree_set_size] = tree;
                    adjacent = true;
                    new_tree_set_size++;
                }


            }


            // what is the number of trees now


        }
    }

    //tree_set_current_size = new_tree_set_size;
    counter--;
    printf("COUNTER %d\n", counter);
    printf("tree_set_current_size %d\n", tree_set_current_size);
    // compare sets again
    if (counter == 0) {
        return;
    } else {
        //connect_sets(maze, tree_set);
    }




}

// Generates a maze based on the Randomized Kruskal algorithm
void gen_kruskal(maze_t* maze) {

    // enables random number generation
    srand((unsigned)time(NULL));

    // number of edges depends on size of maze
    int number_of_edges = (maze->width) * 2 + (maze->height) * 2 - 4;
    printf("Number of edges: %d\n", number_of_edges);

    struct CELL_COORDINATES cell_coordinates;
    cell_coordinates.row = 0;

    int i;

    // record all edges
    struct CELL_COORDINATES edges[number_of_edges];
    for (i = 0; i < (maze->width); i++) {
        // take the first row entirely
        cell_coordinates.column = i;
        edges[i] = cell_coordinates;
    }

    printf("recorded edges from top row: %d\n", i);

    cell_coordinates.row = (maze->height) - 1;
    cell_coordinates.column = 0;

    for (; i < (2 * (maze->width)); i++) {
        // take the last row entirely

        edges[i] = cell_coordinates;
        cell_coordinates.column++;
    }

    printf("recorded edges from top and bottom row: %d\n", i);
    int side_edge_cells = (number_of_edges - i ) / 2;

    printf("edges left after recording top and bottom row for left/right side each: %d\n", side_edge_cells);

    cell_coordinates.column = 0;
    int row_counter = 1;
    int x = i + side_edge_cells;
    // left and right edges
    //from row 1 column 0 to row (height-1) column 0
    for (; i < x; i++) {
        cell_coordinates.row = row_counter;
        edges[i] = cell_coordinates;
        row_counter++;
    }

    printf("recorded edges after left side: %d\n", i);

    row_counter = 1;
    cell_coordinates.column = (maze->width) - 1;

    //from row (width-1) column 0 to row (height-1) column 0
    for (; i < number_of_edges; i++) {
        cell_coordinates.row = row_counter;
        edges[i] = cell_coordinates;
        row_counter++;
    }
    printf("recorded edges after right side: %d\n", i);

    // print all edges
    for (int j = 0; j < number_of_edges; j++) {
        printf("Edge cell_coordinates recorded [column, row] %d: [%d,%d]\n", j, edges[j].column, edges[j].row);
    }

    //----------- EDGES RECORDED -----------//

    // all trees stored here
    struct TREE *tree_set = initialize_tree_set();

    repeated_procedures(maze, tree_set, number_of_edges, cell_coordinates, edges);

    connect_sets(maze, tree_set);


}
