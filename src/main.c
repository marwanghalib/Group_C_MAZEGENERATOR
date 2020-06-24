#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef SDTBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif /* STDIO_H */

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif /* STRING_H */


#ifndef STDDEF_H
#define STDDEF_H
#include <stddef.h>
#endif

#ifndef TILE_H
#define TILE_H
#include <tile.h>
#endif

#ifndef PRINTER_H
#define PRINTER_H
#include <printer.h>
#endif

#ifndef COLL_INPUT_H
#define COLL_INPUT_H
#include <coll_input.h>
#endif /* COLL_INPUT_H */


#define PRG_NAME "maze" /* program name */
#define VERSION  "0.3"  /* version number */

/** @brief This is main function
 *
 * 1. call the function coll_args, collects all the arguments from the user
 * 2. call the function gen_alg, it will generate the algorithm based on the parameter
 * 3. call the function print_maze, it will print the maze
 *  @param argc
 *  @param argv
*/
int main(int argc, char* argv[]){
   //Creation of variables
   maze_t maze;
   tile_set_t* tile_set;
   FILE* fptr = NULL;

   /**coll argus collects the argument and gen_alg solve
   based on the input and there is no return value */

   void (*gen_alg)(maze_t*) = coll_args(argc, argv, &maze, &tile_set, &fptr);
   if(!gen_alg){
   	 return -1;
   }
   (*gen_alg)(&maze);
   print_maze(&maze, tile_set, fptr);
   if(fptr && fptr != stdout){
   	fclose(fptr);
   }
    return 0;
}
