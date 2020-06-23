
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
#include "tile.h"
#endif

#ifndef PRINTER_H
#define PRINTER_H
#include "printer.h"
#endif

#ifndef TILE_DEFAULT_H
#define TILE_DEFAULT_H
#include "tile_default.h"
#endif

#ifndef PARSER_H
#define PARSER_H_H
#include "parser.h"
#endif

#ifndef COLL_INPUT_H
#define COLL_INPUT_H
#include "coll_input.h"
#endif /* COLL_INPUT_H */


#define PRG_NAME "maze" /* program name */
#define VERSION  "0.3"  /* version number */



void init_test_maze_1(maze_t* maze, FILE* myFile){
    maze->input_file = myFile;
}

int main(int argc, char* argv[]){
	
	//Example of a file pointer containing a maze
	FILE *fptr;
	fptr = fopen("ExampleOutputFile.txt","r+");

    //Initializing test maze
    maze_t myMaze;
    maze_t *pmyMaze = &myMaze;
    init_test_maze_1(pmyMaze,fptr);

    //Initializing tile set
    tile_set_t myTileSet;
    tile_set_t *pmyTileSet = &myTileSet;
    pmyTileSet = TILE_SET_HEDGE;
	
	//Testing parser
	parse_maze(pmyMaze);
	
	//Testing my print function
    print_maze(pmyMaze, pmyTileSet , stdout);
	
	fclose(fptr);

    return 0;
}
