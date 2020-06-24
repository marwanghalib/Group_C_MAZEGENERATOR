#ifndef MAZE_H
#define MAZE_H
#include "maze.h"
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


#ifndef GEN_ALGS_H
#define GEN_ALGS_H
#include "gen_algs.h"
#endif


#define NORTH 1
#define SOUTH 2
#define EAST 4
#define WEST 8
#define DIRECTIONS_SIZE 4

int n, top = -1, *stack;

struct backtrack_extra {
    /* put things that you want to store per cell here
    They are initialized to 0 */
};


//-----------------------------------

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

int opposite_direction(int direction) {
    int opposed_direction;
    switch (direction) {
    case NORTH :
        opposed_direction = SOUTH;
        break;
    case SOUTH :
        opposed_direction = NORTH;
        break;
    case EAST :
        opposed_direction = WEST;
        break;
    case WEST :
        opposed_direction = EAST;
        break;
    }
    return opposed_direction;
}

void shuffle(int *array, size_t n)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int usec = tv.tv_usec;
    srand48(usec);


    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48() * (i + 1));
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

bool inRange(unsigned low, unsigned high, unsigned x)
{
    return (low <= x && x <= high);
}

void heap_method(int x, int y, maze_t* maze) {

    int nx;
    int ny;

    // any neighbours to visit?
    // list of directions
    int directions[DIRECTIONS_SIZE] = {NORTH, SOUTH, EAST, WEST};
    // shuffle the list
    shuffle(directions, DIRECTIONS_SIZE);
    nx = move_x(directions[0]) + x;
    ny = move_y(directions[0]) + y;

    bool y_in_range = inRange(0, maze->height - 1, ny);
    bool x_in_range = inRange(0, maze->width - 1, nx);
    //bool is_zero = maze[nx][y] == 0;

    //printf("ITERATION %d: Y in range %d\n", i, y_in_range);
    //printf("ITERATION %d: X in range %d\n", i, x_in_range);
    //printf("ITERATION %d: cell is zero %d\n", i, is_zero);

    //if (y_in_range && x_in_range && is_zero) {
        // put neighbor on the stack



    //}
}
/** @brief This function generates backtrack algorithm
*  A backtracking algorithm is a recursive
*  algorithm that attempts to solve a given problem by
*  testing all possible paths towards a solution until a solution is found.
*  Each time a path is tested, if a solution is not found, the algorithm backtracks to
*  test another possible path and so on till a solution is found or all paths have been tested
*  @param maze_t* maze
*  @return void
*/
void gen_backtrack(maze_t* maze) {

    set_size_of_extra(sizeof(struct backtrack_extra), maze);

    /* Do the generation here */

    //Displaying array elements
    printf("STARTING 2-D array elements:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //printf("%d ", maze[i][j]);
            if (j == (4 - 1)) {
                printf("\n");
            }
        }
    }

    heap_method(0, 0, maze);

    //Displaying array elements
    printf("ENDING 2-D array elements:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //printf("%d ", maze[i][j]);
            if (j == (4 - 1)) {
                printf("\n");
            }
        }
    }
}

// Push to the stack
void push(int x) {
    if (top == n) return;
    stack[++top] = x;
}

// pop teh top of the stack
int pop() {
    if (top == -1) return -1;
    return stack[top--];
}

// check the top of the stack
int peek() {
    if (top == -1) return -1;
    return stack[top];
}

// display the entire stack
void display() {
    for (int i = top ; i > -1 ; i--) printf("%d ", stack[i]);
    printf("\n\n");
}
