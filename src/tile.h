#ifndef MAZE_H
#define MAZE_H
#include <maze.h>
#endif


typedef struct tile_set{
    char *empty;
    char *before;
    char *after;
    char *start;
    char *end;
    char *h_wall;
    char *v_wall;
    char *corner[16];
} tile_set_t;

/**
  is
    delete and free a tile_set
  ensure
    no memory is leaked
  enddungeon
*/
int delete_tile_set(tile_set_t* set);

/**
  is
    allocate and init a tileset with defaults and specified wall string
  requires
    wall is a valid null terminated string
  do
    copies from and does not retain argument pointer
      caller still owns the string
  ensures
    tile_set is in a valid state
    default space is " "
    default start is "<"
    default end is   ">"
    both walls and all corners are set to wall
  end
*/
tile_set_t* new_tile_set(char* wall);

/**
  is
    like 'new_tile_set' but takes both walls and a corner
  requires
    all arguments are valic null terminated strings
  do
    copies from and does not retain argument pointers
      caller still owns them
  ensures
    tile_set is in a valid state
    default space is " "
    default start is "<"
    default end is   ">"
    h_wall and v_wall are set matching the arguments
    all 16 corners are set to corner
*/
tile_set_t* new_tile_set_plus(char* h_wall, char* v_wall, char* corner);


/**
  is
    like 'new_tile_set_pluss' but takes all 16 corners
  requires
    all arguments are valic null terminated strings

    corner numbers are described below, add row and column number

       0   1   2   3
           |       |
     0 .   .  -.  -.

           |       |
     4 .   .  -.  -.
       |   |   |   |
           |       |
     8 .-  .- -.- -.-

           |       |
    12 .-  .- -.- -.-
       |   |   |   |

    alternatly,
    cross_north * 1 +
    cross_west  * 2 +
    west        * 4 +
    north       * 8

  ensure
    tile_set is in a valid state
    default space is " "
    default start is "<"
    default end is   ">"
    all other fields reflect thair argument
  end
*/
tile_set_t* new_tile_set_full_corners(char* h_wall, char* v_wall, char *corners[16]);


/**
  is
    like 'new_tile_set_full_corners' but also assigns over default space start and end characters,
      and allows you to specify a char sequence to be printed before and another to be printed after the maze
  requires
    see 'new_tile_set_full_corners'
  ensures
    tile_set is in a valid state
    all fields reflect their arguments
  end
*/
tile_set_t* new_tile_set_no_defaults(char* empty, char* start, char* end,
        char* h_wall, char* v_wall, char* before, char* after, char *corners[16]);


/**
  is
    a way to get the correct corner based on a cell_t
  requires
    set is a valid tile_set
    a valid cell_t
  do
    read cell.wall_east, cell.wall_south, cell.wall_west, cell.wall_north
    to calculate value of corner
  ensures
    the char* returned is the correct corner reflecting

*/
char* get_corner(const tile_set_t* set, cell_t cell);

