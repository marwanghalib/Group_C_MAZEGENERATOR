/**
  This funcion will print help
  information when the user inputs the
  wrong value
*/
void print_help();

/**
  This funcion will print
  version information whent he
  user inputs the version
*/
void version();

/**
  This function collects all the arguments and output
  it into a location and returns a pointer to the functions.
  Here it takes all the values the user inputs which is height
  width, bias, algorithm, once everything is collected
  it will be passed to the init maze, to initialize, and gen_alg for
  the user chosen option and tile set for the user chosen
*/
void (*coll_args (int argc, char **argv,maze_t* maze,tile_set_t** tile_set, FILE** output_file))(maze_t*);

