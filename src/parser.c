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
	char my_char;
	FILE *fptr;
	tile_set_t myTileSet;
    tile_set_t *pmyTileSet = &myTileSet;
	
	/*Define the width and height of the maze. Height of maze will be a defult of 1 and will be incremented accordingly via add_row()*/
	int wid, hei = 1;
	
	
	/*Point our file pointer to the file that contains the maze*/
	fptr = my_maze->input_file;
	
	/*Measure the width of the maze'*/
	int counter = 0;
	
	my_char = fgetc(fptr); 
    while (my_char	 != EOF) 
    { 
		/*Stop when you see a new line (end of row)*/
		if(my_char == '\n'){
			break;
		}
        counter++;
        my_char = fgetc(fptr); 
    } 
	
	/*Calculating the width of the maze based on the first row*/
	wid = (counter - 1)/2;
	counter++;
	/*Initiate the maze with default height of 1;*/
	init_maze(wid, hei, my_maze);
	
	/*Start making the maze*/
	cell_t c;
	int x = 0,y = 0;
	int done_flag = 0;
	set_size_of_extra(sizeof(bool), my_maze);
	bool* extra;
		
	
	while(!done_flag){
		/*Initially set done flag as true. If this is not true, it will be set to false in the loop*/
		done_flag = 1;
		/*First loop to set vertical row*/
		//printf("First loop ran here\n");
		for(x = 0; x <counter; x++){
			my_char = fgetc(fptr); 
			/*Checking for the west wall*/
			if(x%2 == 0){
				if(my_char!=' '){
					c = get_cell(my_maze, x/2, y);
					c.west  = true;
					set_cell(c, x/2, y, my_maze);
				}
				else {
					c = get_cell(my_maze, x/2, y);
					c.west  = false;
					set_cell(c,  x/2, y, my_maze);
				}
			}
			/*Checking for the inside of the cell*/
			else{
				if(my_char==' '){
					c = get_cell(my_maze, x/2, y);
					//c.empty  = true;
					set_cell(c, x/2, y, my_maze);
				}
				else if(my_char=='.'){
					c = get_cell(my_maze, x/2, y);
					//c.full  = true;
					set_cell(c,  x/2, y, my_maze);
					extra = get_extra(my_maze, x/2, y);
					extra[0] = true;
				}
				else if(my_char=='<'){	
					c = get_cell(my_maze, x/2, y);
					c.start  = true;
					set_cell(c, x/2, y, my_maze);
				}
				else if(my_char=='>'){
					c = get_cell(my_maze, x/2, y);
					c.end  = true;
					set_cell(c, x/2, y, my_maze);
				}
			}
		}
		
		
		//printf("Second loop ran here \n");
		/*Second loop to set horizontal row*/
		for(x=0; x<counter;x++){
			my_char = fgetc(fptr); 
			/*Don't care about corners*/
			if(x%2 == 0){
				//c = get_cell(my_maze, x/2, y);
				//set_cell(c, x/2, y, my_maze);
				continue;
			}
			/*Setting the south wall*/
			else{
				if(my_char!=' '){
					c = get_cell(my_maze, x/2, y);
					c.south  = true;
					set_cell(c, x/2, y, my_maze);
				}
				else{
					c = get_cell(my_maze, x/2, y);
					c.south  = false;
					set_cell(c, x/2, y, my_maze);
					done_flag = 0;
				}
			}
		}
		
		/*If it is not the last row, add a row and increment y*/
		if(done_flag == 0){
			y++;
			add_row(my_maze);
		}
		else{
			c = get_cell(my_maze, x/2, y);
			c.end  = true;
			set_cell(c, x/2, y, my_maze);
		}
	}

	return;
}
