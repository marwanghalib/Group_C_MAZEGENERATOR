#ifndef MAZE_H
#define MAZE_H
#include <maze.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef SDTBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif

#define min_width    1
#define max_width    25
#define min_height   1
#define max_height   25
#define margin       10
#define row_add_reps 5



bool add_row_increases_height_by_1_on_sucsess(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
	    for(int w = min_width; w <= max_width; w++){
	        for(int h = min_height; h <= max_height; h++){
	            init_maze(w, h, &maze);
	            bool clean = true;
	            for(int i = 0; i< reps; i++){clean &= add_row(&maze);}
	            if(clean && maze.height != h+reps){
	                destroy_maze(&maze);
	                return false;
	            }
	            destroy_maze(&maze);
	        }
	    }
    }
    return true;
}

bool add_row_does_not_update_start_and_end(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
	    for(int w = min_width; w <= max_width; w++){
	        for(int h = min_height; h <= max_height; h++){
	            init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
	            if(!(maze.end_x == maze.width-1 && maze.end_y == h-1 && maze.start_x == 0 && maze.start_y == 0)){
	                destroy_maze(&maze);
	                return false;
	            }
	            destroy_maze(&maze);
	        }
	    }
    }
    return true;
}


bool add_row_does_not_create_extra(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = -margin; x < w+margin; x++){
                    for(int y = -margin; y < h+reps+margin; y++){
                        if(get_extra(&maze, x, y)){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool add_row_presurves_get_extra_outside_range_returns_null(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
                set_size_of_extra(sizeof(int), &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
            
                for(int x = -margin; x < w+margin; x++){
                    for(int y = -margin; y < 0; y++){
                        if(get_extra(&maze, x, y)){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                    for(int y = h+reps; y < h+reps+margin; y++){
                        if(get_extra(&maze, x, y)){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
            
                for(int y = -margin; y < h+reps+margin; y++){
                    for(int x = -margin; x < 0; x++){
                        if(get_extra(&maze, x, y)){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                    for(int x = w; x < w+margin; x++){
                        if(get_extra(&maze, x, y)){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool add_row_sets_new_extra_to_default_value_0(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
                set_size_of_extra(sizeof(int), &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
	            
                for(int x = 0; x < w; x++){
                    for(int y = 0; y < h+reps; y++){
                        int* t = get_extra(&maze, x, y);
                        if(*t){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}


bool add_row_extends_extra_writable_memory(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
                set_size_of_extra(sizeof(int), &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = 0; x < w; x++){
                    for(int y = 0; y < h+reps; y++){
                        int* t = get_extra(&maze, x, y);
                        *t = ((x+1)<<4)*(y+1);
                    }
                }
                for(int x = 0; x < w; x++){
                    for(int y = 0; y < h+reps; y++){
                        int* t = get_extra(&maze, x, y);
                        if(*t != ((x+1)<<4)*(y+1)){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool add_row_does_not_reset_the_contents_of_extra(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
                set_size_of_extra(sizeof(int), &maze);
                for(int x = 0; x < w; x++){
                    for(int y = 0; y < h; y++){
                        int* t = get_extra(&maze, x, y);
                        *t = ((x+1)<<4)*(y+1);
                    }
                }
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = 0; x < w; x++){
                    for(int y = 0; y < h; y++){
                        int* t = get_extra(&maze, x, y);
                        if(*t != ((x+1)<<4)*(y+1)){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool add_row_new_walls_are_present(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = 0; x < w; x++){
                    for(int y = 0; y < h+reps; y++){
                        cell_t cell = get_cell(&maze, x, y);
                        if(!cell.north || !cell.south || !cell.east || !cell.west){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
        return true;
    }
}

bool get_cell_is_safe_even_far_out_of_bounds_even_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = -margin; x < w+margin; x++){
                    for(int y = -margin; y < h+reps+margin; y++){
                        volatile cell_t v_cell = get_cell(&maze, x, y);
                        cell_t cell = get_cell(&maze, x, y);
                        if(!cells_are_equal(v_cell, cell)){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool set_cell_is_safe_even_far_out_of_bounds_even_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = -margin; x < w+margin; x++){
                    for(int y = -margin; y < h+reps+margin; y++){
                        cell_t cell = get_cell(&maze, x, y);
                        cell.north = !cell.north;
                        cell.south = !cell.south;
                        cell.east = !cell.east;
                        cell.west = !cell.west;
                        cell.cross_north = !cell.cross_north;
                        cell.cross_west = !cell.cross_west;
                        cell.start = !cell.start;
                        cell.end = !cell.end;
                        set_cell(cell, x, y, &maze);
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool get_cell_no_vertical_walls_out_of_bounds_even_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = -margin; x < w+margin; x++){
                    for(int y = -margin; y < h+reps+margin; y++){
                        if(x < 0 || x > w || y < 0 || y >= h+reps){
                            cell_t cell = get_cell(&maze, x, y);
                            if(cell.west){
                                destroy_maze(&maze);
                                return false;
                            }
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool get_cell_no_horizontal_walls_out_of_bounds_eve_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = -margin; x < w+margin; x++){
                    for(int y = -margin; y < h+reps+margin; y++){
                        if(x < 0 || x >= w || y < 0 || y > h+reps){
                            cell_t cell = get_cell(&maze, x, y);
                            if(cell.north){
                                destroy_maze(&maze);
                                return false;
                            }
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}



bool get_cell_shows_parimiter_walls_even_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = 0; x < w; x++){
                    cell_t cell_north = get_cell(&maze, x, 0);
                    cell_t cell_south = get_cell(&maze, x, h+reps);
                    if(!cell_north.north || !cell_south.north){
                        destroy_maze(&maze);
                        return false;
                    }
                }
                for(int y = 0; y < h+reps; y++){
                    cell_t cell_west = get_cell(&maze, 0, y);
                    cell_t cell_east = get_cell(&maze, w, y);
                    if(!cell_west.west || !cell_east.west){
                        destroy_maze(&maze);
                        return false;
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}



bool set_cell_updates_vertical_walls_in_the_maze_even_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = 1; x < w; x++){
                    for(int y = 0; y < h+reps; y++){
                        cell_t cell = get_cell(&maze, x, y);
                        cell.west = !cell.west;
                        set_cell(cell, x, y, &maze);
                    
                        if(cell.west != get_cell(&maze, x, y).west){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}


bool set_cell_updates_horizontal_walls_in_the_maze_even_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = 0; x < w; x++){
                    for(int y = 1; y < h+reps; y++){
                        cell_t cell = get_cell(&maze, x, y);
                        cell.north = !cell.north;
                        set_cell(cell, x, y, &maze);
                    
                        if(cell.north != get_cell(&maze, x, y).north){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool set_cell_handles_overlap_even_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = -margin; x < w+margin; x++){
                    for(int y = -margin; y < h+reps+margin; y++){
                        cell_t cell = get_cell(&maze, x, y);
                    
                        cell.north = !cell.north;
                        cell.west = !cell.west;
                        cell.cross_north = !cell.cross_north;
                        cell.cross_west = !cell.cross_west;
                    
                        set_cell(cell, x, y, &maze);
                        cell           = get_cell(&maze, x,   y);
                        cell_t cell_n  = get_cell(&maze, x,   y-1);
                        cell_t cell_w  = get_cell(&maze, x-1, y);
                        cell_t cell_nw = get_cell(&maze, x-1, y-1);
                        if( cell.north       != cell_n.south ||
                            cell.cross_north != cell_n.west  ||
                            cell.west        != cell_w.east  ||
                            cell.cross_west  != cell_w.north ||
                            cell.cross_north != cell_nw.east ||
                            cell.cross_west  != cell_nw.south)
                        {
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

bool set_cell_handles_start_and_end_even_after_add_row(void){
    maze_t maze;
    for(int reps = 1; reps <= row_add_reps; reps++){
        for(int w = min_width; w <= max_width; w++){
            for(int h = min_height; h <= max_height; h++){
                init_maze(w, h, &maze);
	            for(int i = 0; i< reps; i++){add_row(&maze);}
                for(int x = 0; x < w; x++){
                    for(int y = 0; y < h+reps; y++){
                        cell_t cell = get_cell(&maze, x, y);
                        cell.start = true;
                        set_cell(cell, x, y, &maze);
                        if(maze.start_x != x || maze.start_y != y || !get_cell(&maze, x, y).start){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
            
                for(int x = 0; x < w; x++){
                    for(int y = 0; y < h+reps; y++){
                        cell_t cell = get_cell(&maze, x, y);
                        cell.end = true;
                        set_cell(cell, x, y, &maze);
                        if(maze.end_x != x || maze.end_y != y || !get_cell(&maze, x, y).end){
                            destroy_maze(&maze);
                            return false;
                        }
                    }
                }
                destroy_maze(&maze);
            }
        }
    }
    return true;
}

/* Takes the name of a function that is passed no arguments, and prints if that function returns true and it's name*/
#define test(f) printf("[%s] " #f "\n", (f())?("\033[0;32mPassed\033[0m"):("\033[0;31mFailed\033[0m"))

int main(){
    
    test(add_row_increases_height_by_1_on_sucsess);
    test(add_row_does_not_update_start_and_end);
    test(add_row_does_not_create_extra);
    test(add_row_presurves_get_extra_outside_range_returns_null);
    test(add_row_sets_new_extra_to_default_value_0);
    test(add_row_extends_extra_writable_memory);
    test(add_row_does_not_reset_the_contents_of_extra);
    test(add_row_new_walls_are_present);
    test(get_cell_is_safe_even_far_out_of_bounds_even_after_add_row);
    test(set_cell_is_safe_even_far_out_of_bounds_even_after_add_row);
    test(get_cell_no_vertical_walls_out_of_bounds_even_after_add_row);
    test(get_cell_no_horizontal_walls_out_of_bounds_eve_after_add_row);
    test(get_cell_shows_parimiter_walls_even_after_add_row);
    test(set_cell_updates_vertical_walls_in_the_maze_even_after_add_row);
    test(set_cell_updates_horizontal_walls_in_the_maze_even_after_add_row);
    test(set_cell_handles_overlap_even_after_add_row);
    test(set_cell_handles_start_and_end_even_after_add_row);
    
    return 0;
}

#undef test

#undef min_width
#undef max_width
#undef min_height
#undef max_height
#undef margin
#undef row_add_reps
