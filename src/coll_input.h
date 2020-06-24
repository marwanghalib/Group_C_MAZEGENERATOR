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


void (*coll_args (int argc, char **argv,maze_t* maze,tile_set_t** tile_set, FILE** output_file))(maze_t*);

