#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif /* STDIO_H */

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif /* STRING_H */


#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif /* STRING_H */

#ifndef MAIN_H
#define MAIN_H
#include "main.h"
#endif /* MAIN_H */

#ifndef MAZE_H
#define MAZE_H
#include "maze.h"
#endif

#ifndef TILE_H
#define TILE_H
#include "tile.h"
#endif

#ifndef TILE_DEFAULT_H
#define TILE_DEFAULT_H
#include "tile_default.h"
#endif

#ifndef COLL_INPUT_H
#define COLL_INPUT_H
#include "coll_input.h"
#endif /* COLL_INPUT_H */

#define PRG_NAME "maze" /* program name */
#define VERSION  "0.3"  /* version number */


/* Display help information and exit succesfully
 */
void help(void)
{
    printf(" %s - a maze generator and solver\n\
Usage: %s [options]\n\
\n\
  --height              How tall is the maze\n\
  --width               How tall is the maze\n\
  --size or -s          How wide and tall is the maze\n\
  --bias or -b          How biased is the maze: >1 more horizontal hallways <1 more vertical hallways\n\
  -a or --algorithm     Which algorithm to use (backtracker / Sidewinder) \n\
  -v or --version       Display program name and version number\n\
  -t or --tileset	    What characters to use (dungeon / hedge) to represent the walls of the maze in the output\n\
  -o or	--output	    Where to send the output\n\
  --solve	            Solve the maze\n\
  -i or	--input	        Read stdin as FILE\n",
            PRG_NAME, PRG_NAME);

	//exit(EXIT_SUCCESS);
}
/* Display version information and exit succesfully
 */
void version(void)
{
	printf("\
%s %s\n\
\n\
The Program name and the version number is.\n",
	       PRG_NAME, VERSION);

	exit(EXIT_SUCCESS);
}

void gen_backtrack(maze_t* maze){}
void gen_sidewinder(maze_t* maze){}

/*
This function collects all the arguments and output it into a location and returns a
pointer to the functions */


void (*coll_args (int argc, char **argv,maze_t* maze,tile_set_t** tile_set, FILE** output_file))(maze_t*){
    //assigning default values to the variables which will reset if user input something
    int width = 10;
    int height = 5;
    double bias = 1.0;
    char* algorithm = "backtrack";
    char* tile_sets = "hedge";
    int i = 0;
    int status = 0;
    char* filename = "maze.txt";
    *output_file = stdout;

    while(i < argc) {
     i++;
     if (strcmp(argv[i], "--h") == 0 || strcmp(argv[i], "--help") == 0){
        help();

        //return NULL;
     }
     else if (strcmp(argv[i], "--v") == 0 || strcmp(argv[i], "--version") == 0){
        version();
            //return NULL;
     }
     else if(strcmp(argv[i], "--width") == 0){
            i++;
            if(argv[i] == NULL){
                help();
                //return 0;
            }
            if (atoi(argv[i]) > 0){
                width = atoi(argv[i]);
            }
            else{
               help();
             //return 0;
            }
     }
     else if(strcmp(argv[i], "--height") == 0){
              i++;
              if(argv[i] == NULL){
                help();
                //return NULL;
            }
            if (atoi(argv[i]) > 0){
                height = atoi(argv[i]);
            }
            else{
               help();
             //return 0;
            }
     }
     else if(strcmp(argv[i], "--bias") == 0 || strcmp(argv[i], "-b") == 0){
             i++;
             if(argv[i] == NULL){
                help();
                //return NULL;
             }
             bias = atof(argv[i]);
             //i++;
     }
     /*else if(strcmp(argv[i], "--size") == 0 || strcmp(argv[i], "-s") == 0){
             i++;
             int j = i;
             if((argv[j] == NULL)|| (argv[j+1] == NULL)) {
                help();
                //return NULL;
             }
             if ((atoi(argv[j]) > 0)||(atoi(argv[j+1]) > 0)){
                width = atoi(argv[j]);
                height = atoi(argv[j+1]);
                i = i+1;
             }
             else{
               help();
             //return 0;
             }
     }*/
     else if(strcmp(argv[i], "--size") == 0 || strcmp(argv[i], "-s") == 0){
             i++;
             //int j = i;
             if((argv[i] == NULL)|| (argv[i+1] == NULL)) {
                help();
                //return NULL;
             }
             if ((atoi(argv[i]) > 0)||(atoi(argv[i+1]) > 0)){
                width = atoi(argv[i]);
                height = atoi(argv[i+1]);
                i = i+1;
             }
             else{
               help();
             //return 0;
             }
     }
     else if(((strcmp(argv[i], "--algorithm") == 0) || (strcmp(argv[i], "-a") == 0))){
             i++;
             if(argv[i] == NULL){
                help();
                //return NULL;
             }
             if ((strcmp(argv[i], "sidewinder")) == 0) {
                algorithm = "sidewinder";
             }
             else if ((strcmp(argv[i], "backtracker")) == 0) {
                algorithm = "backtracker";
             }
            else{
               help();
             //return 0;
            }

     }
     else if(strcmp(argv[i], "--tileset") == 0 || strcmp(argv[i], "-t") == 0){
             i++;
             if(argv[i] == NULL){
                help();
                //return NULL;
             }
             if ((strcmp(argv[i], "dungeon")) == 0) {
                tile_sets = "dungeon";
             }
             else if ((strcmp(argv[i], "hedge")) == 0) {
                tile_sets = "hedge";
             }
            else{
               help();
             //return 0;
             }
     }
     else if(strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0){
             i++;
             if (argv[i] == NULL) {
                help();
                //return NULL;
             }
             filename = argv[i];
             *output_file = fopen(filename, "w");
     }
     if(i==(argc-1)){
            break;
     }

  }
  //pass values to initialize maze
  status = init_maze(width,height,maze);
  //passing the values to bias function
  set_bias(bias,maze);

  if (strcmp(tile_sets, "dungeon") == 0){
    tile_set = &TILE_SET_DUNGEN;
  }
  else{
    tile_set = &TILE_SET_HEDGE;
  }
  //choose algorithm
  if (strcmp(algorithm, "sidewinder") == 0){
    return &gen_sidewinder;
  }
  else{
    return &gen_backtrack;
  }
}


int main(int argc, char* argv[]){

   maze_t maze;
   tile_set_t* tile_set;
   FILE* fptr = NULL;
   coll_args (argc, argv, &maze, &tile_set, &fptr)(&maze);



    return 0;
}


