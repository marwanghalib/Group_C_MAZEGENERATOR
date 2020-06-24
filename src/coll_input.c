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

#ifndef GEN_ALGS_H
#define GEN_ALGS_H
#include "gen_algs.h"
#endif

#define PRG_NAME "maze" /* program name */
#define VERSION  "0.3"  /* version number */


/* Display help information and exit succesfully
 */
void print_help(void)
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
	printf("%s %s\n\nThe Program name and the version number is.\n", PRG_NAME, VERSION);

	exit(EXIT_SUCCESS);
}


/** @brief This function collects all the arguments and output it into a location and returns a
 *       pointer to the functions.
 *
 *  This function collects the arguments that user provided during the inoput when he runs the maze
 *  all the value are collected height, width, tiles, using agrv and once it is collected it will
 *  be sent to the first funtion which is initialize maze and this will return a value and then it is
 *  passed to the algorithm which is sidewinder or backtrack or kriuskel based on the
 *  user input funtion. This function will also gives an option to chose were the output should be displayed
 *  wheter its stdout or file path
 *
 *  @param int argc
 *  @param char **argv
 *  @param maze_t* maze
 *  @param tile_set_t** tile_set
 *  @paramFILE** output_file
 *  @return void
 */


void (*coll_args (int argc, char **argv,maze_t* maze,tile_set_t** tile_set, FILE** output_file))(maze_t*){
    //assigning default values to the variables which will reset if user input something
    int width = 10;
    int height = 5;
    double bias = 1.0;
    char* algorithm = "backtrack";
    char* tile_sets = "hedge";
    int i = 1;
    char* output_file_path = NULL;

    while(i < argc) {
     //verify is user inputs help and call help function
     if (strcmp(argv[i], "--h") == 0 || strcmp(argv[i], "--help") == 0){
            print_help();
            i++;
            return NULL;
     }
     //verify is user inputs version and call version function
     else if (strcmp(argv[i], "--v") == 0 || strcmp(argv[i], "--version") == 0){
        version();
        i++;
        return NULL;
     }
     //verify is user inputs width and assigns value
     else if(strcmp(argv[i], "--width") == 0){
            i++;
            if(argv[i] == NULL){
                print_help();
                return NULL;
            }
            if (atoi(argv[i]) > 0){
                width = atoi(argv[i]);
            }
            else{
               print_help();
               return NULL;
            }
            i++;
     }
     //verify is user inputs height and assigns value
     else if(strcmp(argv[i], "--height") == 0){
              i++;
              if(argv[i] == NULL){
                print_help();
                return NULL;
            }
            if (atoi(argv[i]) > 0){
                height = atoi(argv[i]);
            }
            else{
               print_help();
               return NULL;
            }
            i++;
     }
     //verify is user inputs bias and assigns value
     else if(strcmp(argv[i], "--bias") == 0 || strcmp(argv[i], "-b") == 0){
             i++;
             if(argv[i] == NULL){
                print_help();
                return NULL;
             }
             bias = atof(argv[i]);
             i++;
     }
     //verify is user inputs size and assigns value
     else if(strcmp(argv[i], "--size") == 0 || strcmp(argv[i], "-s") == 0){
             i++;
             if((argv[i] == NULL)|| (argv[i+1] == NULL)) {
                print_help();
                return NULL;
             }
             if ((atoi(argv[i]) > 0)||(atoi(argv[i+1]) > 0)){
                width = atoi(argv[i]);
                height = atoi(argv[i+1]);
                i = i+2;
             }
             else{
               print_help();
               return NULL;
             }
     }
     //verify is user inputs algorithm and assigns value
     else if (strcmp(argv[i], "--algorithm") == 0 || strcmp(argv[i], "-a") == 0){
             i++;
             if(argv[i] == NULL){
                print_help();
                return NULL;
             }
             if (((strcmp(argv[i], "sidewinder")) == 0 || atoi(argv[i]) == 0)) {
                algorithm = "sidewinder";
             }
             else if ((strcmp(argv[i], "backtrack")) == 0 || atoi(argv[i]) == 1){
                algorithm = "backtrack";
             }
            else{
               print_help();
               return NULL;
            }
            i++;
     }
     //verify is user inputs tileset and assigns value
     else if (strcmp(argv[i], "--tileset") == 0 || strcmp(argv[i], "-t") == 0){
             i++;
             if(argv[i] == NULL){
                print_help();
                return NULL;
             }
             if ((strcmp(argv[i], "hedge")) == 0 || atoi(argv[i]) == 0) {
                tile_sets = "hedge";
             }
             else if ((strcmp(argv[i], "dungeon")) == 0 || atoi(argv[i]) == 1) {
                tile_sets = "dungeon";
             }
            else{
               print_help();
               return NULL;
            }
            i++;
     }
     //verify is user ouptut 
     else if(strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0){
             i++;
             if (argv[i] == NULL) {
                print_help();
                return NULL;
             }
             output_file_path = argv[i];
             i++;
     }
     else{
        print_help();
        return NULL;
     }
  }
  
  //pass values to initialize maze
  if(init_maze(width, height, maze) <0){
    return NULL; /*error handler code here*/
  }
    
  //pass the values to bias function
  set_bias(bias,maze);
  //user selects the file path 
  if(output_file_path){
    *output_file = fopen(output_file_path, "w");
  }else{
  	*output_file = stdout;
  }
  //
  //pass the values to tile function
  if (strcmp(tile_sets, "hedge") == 0){
    *tile_set = TILE_SET_HEDGE;
  }
  else{
    *tile_set = TILE_SET_DUNGEN;
  }
  //choose algorithm
  if (strcmp(algorithm, "backtrack") == 0) {
    return &gen_backtrack;
  }
  else{
    return &gen_sidewinder;
  }
}



