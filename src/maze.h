#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef STDBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

#ifndef STDDEF_H
#define STDDEF_H
#include <stddef.h>
#endif

typedef struct maze_data maze_data_t;

typedef struct{
    int width;
    int height;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    double bias;
    maze_data_t *data;
} maze_t;


typedef struct{
    struct{
        bool cross_north :1;
        bool cross_west  :1;
        bool west        :1;
        bool north       :1;
        bool east        :1;
        bool south       :1;
        bool start       :1;
        bool end         :1;
    };
}cell_t;

/**
  is
    initialize a maze object with specified 'width', specified 'height',
    start in the top left, and end in the bottom right, at the address 'maze'.
  require
    maze has not been initialize before, or has been destroyed
        if this is not followed, memory will leak
  ensure
    if maze is NULL, return -1
    if malloc fails, return -1
    width = max(width, 1)
    height = max(height, 1)
    start_x == 0
    start_y == 0
    end_x   == width-1
    end_y   == height-1
    maze is in a valid state
    no memory is leaked
  end
*/
int init_maze(int width, int height, maze_t *maze);

/**
  is
    used to set the bias field of a maze
  requires
    0 < bias < inf
    maze is in a valid state
  ensure
    if bias < 1 NOP rather than doing anything
    bias is updated
    maze is in a valid state
  end
*/
void set_bias(double bias, maze_t *maze);

/**
  is
    destroy but do not free the maze at address 'maze'
  require
    maze has been initialized
      trying to destroy an uninitialized maze can segfault or doublefree
  ensure
    no memory is leaked
  end
*/
int destroy_maze(maze_t *maze);

/**
  is
    create and return a cell_t structure describing the
    current state of the maze at 'x' 'y'
  require
    maze is in a valid state
  do
    return information relating to the presence or absence of
    walls at a point x,y in this pattern, true is closed, false is open
      x
     |
    - -
   y | |
      -

    as well as if it is the current start and/or end of the maze
    The 4 marks below are stored in
    '.north', '.east', '.south', and '.west'
      x
      -
    y| |
      -
    The 4 marks below are stored in
    '.cross_north', '.cross_west'
       x
      |
     -
    y
    walls outside of the maze are open
    walls on the edge of the maze are closed
  ensure
    no illigal reads
    the cell represents point x,y
    maze is unchanged
  end
*/
__attribute__ ((pure)) cell_t get_cell(const maze_t *maze, int x, int y);

/**
  is
    updates maze with cell at x,y relating to
      corner_north, corner_west, north, and west,
    ignoring doors outside the body of the maze and ignoring start and end
  requires
    maze is in a valid state
  ensure
    maze is updated
    no illigal writes
    maze is in a valid state
  end
*/
void set_cross(cell_t cell, int x, int y, maze_t *maze);

/**
  is
    updates maze with cell at x,y relating to
    north, south, east, and west,
    ignoring doors outside of the body of the maze, and ignoring start and end
  require
    maze is in a valid state
  ensure
    maze is updated
    no illigal writes
    maze is in a valid state
  end
*/
void set_room(cell_t cell, int x, int y, maze_t *maze);

/**
  is
    update the maze with all information from cell
    ignoring walls outside of the body of the maze
  requires
    maze is in a valid state
  ensure
    excluding walls outside the body of the maze, get_cell(&maze, x, y) == cell
    no illigal writes
    maze is in a valid state
  end
*/
void set_cell(cell_t cell, int x, int y, maze_t *maze);

/**
  do
    return an empty cell. All walls are open and it is not the start or end
*/
__attribute__ ((const)) cell_t make_empty_cell(void);


/**
  do
    compare 2 cells for equality.
    cell_a == cell_b only if all fields match exactly
  note
    this does mean that changes to walls outside the maze
    can make 2 cells that woudl otherwise be equivelant non equal
    This is nessesary because cells do not know where in the maze they go
 */
__attribute__ ((const)) bool cells_are_equal(cell_t a, cell_t b);

/**
  do
    get a pointer to the extra data stored in the maze about this location
  ensure 
    if set_size_of_extra has not been called, 
      or it has been called with a value <= 0, 
      will return null
    if the location x,y is outside the maze, 
      return null
    otherwise
      return a pointer to writable memory of the specified size.
      This memory does not overlap other data.
 */
__attribute__ ((pure)) void* get_extra(const maze_t* maze, int x, int y);

/**
  do
    return true if
      there is some non-0 byte
      stored in the extra data for this position in this maze
 */
__attribute__ ((pure)) bool is_full(const maze_t* maze, int x, int y);

/**
 do
    delete the old extra data if there is anything
    set the maze up for use of the extra data fields
 ensure
    extra data is 0 initialized
    no memory is leaked
 */
int set_size_of_extra(size_t new_size, maze_t* maze);
