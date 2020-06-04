typedef struct maze_data maze_data_t;


typedef struct maze{
    int width;
    int height;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    double bias;
    maze_data_t *data;
} maze_t;


typedef struct cell{
    union{
        uint8_t mask;
        struct{
            _Bool wall_east :1;
            _Bool wall_south:1;
            union{
                _Bool wall_west :1;
                _Bool door_south:1;
            };
            union{
                _Bool wall_north:1;
                _Bool door_east :1;
            };
            _Bool door_north:1;
            _Bool door_west :1;
            _Bool start     :1;
            _Bool end       :1;
        };
    };
} cell_t;



/**
  is
    initialize a maze object with specified 'width', specified 'height',
    start in the top left, and end in the bottom right, at the address 'maze'.
  require
    width >= 0
    height >= 0
    maze != NULL
    maze has not been initialized,
      or has been destroyed since the last time it was initalized
  ensure
    if returns 0
      maze is in a valid state
    else
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
    bias is updated
    maze is in a valid state
  end
*/
void set_bias(double bias, maze_t *maze);

/**
  is
    destroy but do not free the maze at address 'maze'
  require
    maze is not null
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
    -1 <= x < maze->width
    -1 <= y < maze->height
    maze is in a valid state
  do
    return information relating to the presence or absence of
    walls at a point x,y in this pattern, true is closed, false is open

      x
      -
    y| |
      - -
       |

    as well as if it is the current start and/or end of the maze

    The 4 marks below are stored in
    '.door_north', '.door_east', '.door_south', and '.door_west'
      x
      -
    y| |
      -

    The 4 marks below are stored in
    '.wall_north', '.wall_east', '.wall_south', and '.wall_west'
     x
    y |
     - -
      |

    Overlap is handled by the structure of the cell_t structure

    walls outside of the maze are open
    walls on the edge of the maze are closed

  ensure
    no illigal reads
    the cell represents point x,y
    maze is unchanged
  end
*/
cell_t get_cell(maze_t *maze, int x, int y);

/**
  is
    updates maze with cell at x,y relating to doors only,
    ignoring doors at the edge of the maze
  requires
    -1 <= x < maze->width
    -1 <= y < maze->height
    maze is in a valid state
  ensure
    the walls around point x,y are updated
    no illigal writes
    maze is in a valid state
  end
*/
void set_door(cell_t cell, int x, int y, maze_t *maze);

/**
  is
    updates maze with cell at x,y relating to cross of walls only,
    ignoring walls at the edge of, or outside of the maze
  requires
    -1 <= x < maze->width
    -1 <= y < maze->height
    maze is in a valid state
  ensure
    the cross walls south east of x,y are updated
    no illigal writes
    maze is in a valid state
  end
*/
void set_walls(cell_t cell, int x, int y, maze_t *maze);

/**
  is
    updates maze with cell at x,y including the addition of start and end
    ignoring walls at the edge of, or outside of the maze
  requires
    -1 <= x < maze->width
    -1 <= y < maze->height
    maze is in a valid state
  ensure
    each wall described by cell that is in bounds is updated
    no illigal writes
    maze is in a valid state
  end

*/
void set_cell(cell_t cell, int x, int y, maze_t *maze);

/**
  do
    return an empty cell. All walls are open and it is not the start or end
*/
cell_t make_empty_cell(void);
