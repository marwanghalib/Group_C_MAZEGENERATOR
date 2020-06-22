
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



int main(int argc, char* argv[]){

   maze_t maze;
   tile_set_t* tile_set;
   FILE* fptr = NULL;
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
