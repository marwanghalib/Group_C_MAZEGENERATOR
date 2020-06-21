
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


#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif /* STDIO_H */
#define PRG_NAME "maze" /* program name */
#define VERSION  "0.3"  /* version number */

#ifndef MAIN_H
#define MAIN_H

#ifndef STDDEF_H
#define STDDEF_H
#include <stddef.h>
#endif

#ifndef TILE_H
#define TILE_H
#include "tile.h"
#endif

#ifndef MAZE_H
#define MAZE_H
#include "maze.h"
#endif


//#include <main.h>
//#include <coll_input.h>

#endif /* MAIN_H */

#ifndef TILE_DEFAULT_H
#define TILE_DEFAULT_H
#include "tile_default.h"
#endif

#ifndef COLL_INPUT_H
#define COLL_INPUT_H
#include "coll_input.h"
#endif /* COLL_INPUT_H */



int main(int argc, char* argv[]){

   maze_t maze;
   tile_set_t* tile_set;
   FILE* fptr = NULL;
   coll_args(argc, argv, &maze, &tile_set, &fptr);
   if (fptr != NULL){
    fprintf(fptr, "This is testing for fprintf...\n");
    fclose(fptr);
   }
   else{
    printf("file not specified\n");
    //consider this as stdout, as user didnt not entered any file name
   }


    return 0;
}
