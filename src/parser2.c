#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef SDTBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDDEF_H
#define STDDEF_H
#include <stddef.h>
#endif

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

void parse_maze(maze_t *my_maze){
	/*Define variables to store character to be read and the file pointer*/
	char c;
	FILE *fptr;
	tile_set_t myTileSet;
    tile_set_t *pmyTileSet = &myTileSet;
	
	/*Define the width and height of the maze. Height of maze will be a defult of 1 and will be incremented accordingly via add_row()*/
	int wid, hei = 1;
	
	
	/*Point our file pointer to the file that contains the maze*/
	fptr = my_maze->input_file;
	
	/*Measure the width of the maze'*/
	int counter = 0;
	
	c = fgetc(fptr); 
    while (c != EOF) 
    { 
		/*Stop when you see a new line (end of row)*/
		if(c == '\n'){
			break;
		}
        counter++;
        c = fgetc(fptr); 
    } 
	
	
	/*Calculating the width of the maze based on the first row*/
	wid = (counter - 1)/2;
	printf("The maze width is %d\n",wid);
	counter++;
	
	/*Initiate the maze with default height of 1;*/
	init_maze(wid, hei, my_maze);
	
	/*Start making the maze*/
	cell_t c;
	int x = 0,y = 0;
	int done_flag = 0;
		
	
	while(!done_flag){
		done_flag = 1;
		/*First loop to set vertical row*/
		for(x = 0; x <counter; x++){
			c = fgetc(fptr); 
			/*Checking for the west wall*/
			if(x%2 == 0){
				if(c!=' '){
					c = get_cell(my_maze, x/2, y);
					c.west  = true;
					set_cell(c, 0, 0, my_maze);
					counter++;
				}
				else {
					c = get_cell(my_maze, x/2, y);
					c.west  = false;
					set_cell(c, 0, 0, my_maze);
					counter++;
				}
			}
			/*Checking for the inside of the cell*/
			else{
				if(c==' '){
					c = get_cell(my_maze, x/2, y);
					c.empty  = true;
					set_cell(c, 0, 0, my_maze);
					counter++;
				}
				else if(c=='.'){
					c = get_cell(my_maze, x/2, y);
					c.full  = true;
					set_cell(c, 0, 0, my_maze);
					counter++;
				}
				else if(c=='<'){	
					c = get_cell(my_maze, x/2, y);
					c.start  = true;
					set_cell(c, 0, 0, my_maze);
					counter++;
				}
				else if(c=='>'){
					c = get_cell(my_maze, x/2, y);
					c.end  = true;
					set_cell(c, 0, 0, my_maze);
					counter++;
				}
			}
		}
		
		counter = 0;
		c = fgetc(fptr); 
		
		/*Second loop to set horizontal row*/
		for(x=0; x<counter;x++){
			c = fgetc(fptr); 
			/*Don't care about corners*/
			if(x%2 == 0){
				counter++;
				continue;
			}
			/*Setting the south wall*/
			else{
				if(c!=' '){
					c = get_cell(my_maze, x/2, y);
					c.south  = true;
					set_cell(c, 0, 0, my_maze);
					counter++;
				}
				else{
					c = get_cell(my_maze, x/2, y);
					c.south  = false;
					set_cell(c, 0, 0, my_maze);
					counter++;
					done_flag = 0;
				}
			}
		}
		
		if(done_flag == 0){
			y++;
		}
	}

	return 0;
}
