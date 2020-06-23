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

void print_maze(maze_t *my_maze, const tile_set_t *my_tile_set , FILE* destination){

    /*Creating variables for the maze width and height*/
    int wid = my_maze->width, hei = my_maze->height;

    /*Stop if 0xX or Xx0*/
    if(wid == 0 || hei == 0){
        return;
    }

    /*Creating variable to store cell data*/
    cell_t cell;

    int x,y;

    /*Print "before" before starting maze printing*/
    fprintf(destination, "%s", my_tile_set->before);

    /*Run loop for number of rows*/
    for(y=0; y<=hei; y++){
        //Run loop for number of columns*/
        //First loop of the row will set the corners and north wall*/
        for(x = 0; x<wid; x++){
            cell = get_cell(my_maze, x, y);
            //Adding full instead of empty on north wall between two full cells
            if((is_full(my_maze,x,y))&&is_full(my_maze,x,y-1)&&(cell.north==false)){
                fprintf(destination, "%s%s", get_corner(my_tile_set,cell), my_tile_set->full);
            }
            else{
                fprintf(destination, "%s%s", get_corner(my_tile_set,cell), (cell.north)?(my_tile_set->h_wall):(my_tile_set->empty));
            }
        }
        /*Run case for row+1 to complete the west wall of last column*/
        cell = get_cell(my_maze, wid, y);
        fprintf(destination, "%s\n", get_corner(my_tile_set,cell));

        /*Second loop of the row will set the west wall and the middle of the cell*/
        for(x = 0; x<wid;x++){
            cell = get_cell(my_maze, x, y);
            //Adding full instead of empty on west wall between two full cells
            if((is_full(my_maze,x,y))&&is_full(my_maze,x-1,y)&&(cell.west==false)){
                fprintf(destination,"%s",my_tile_set->full);
                fprintf(destination,"%s",(cell.start)?(my_tile_set->start):((is_full(my_maze,x,y))?(my_tile_set->full):(my_tile_set->empty)));
            }
            else{
                fprintf(destination, "%s%s", (cell.west)?(my_tile_set->v_wall):(my_tile_set->empty), (cell.end)?(my_tile_set->end):((cell.start)?(my_tile_set->start):((is_full(my_maze,x,y))?(my_tile_set->full):(my_tile_set->empty))));
        }   }
        /*Run case for column+1 to complete the south wall of bottom row*/
        cell = get_cell(my_maze, wid, y);
        fprintf(destination, "%s\n", (cell.west)?(my_tile_set->v_wall):(my_tile_set->empty));
    }

    /*Print "after" after maze printing has completed*/
    fprintf(destination, "%s", my_tile_set->after);


    return;
}
