#ifndef MAZE_H
#define MAZE_H
#include <maze_h>
#endif

void gen_sidewinder(maze_t* maze);
void gen_backtrack(maze_t* maze);



/**
 remove these when they are defined properly
 */
 
 void gen_sidewinder(maze_t* maze){
    printf("sidewinder %d by %d bias %f\n", maze->width, maze->height, maze->bias);
 	
 }
 
 void gen_backtrack(maze_t* maze){
    printf("backtrack %d by %d bias %f\n", maze->width, maze->height, maze->bias);
 	
 }
