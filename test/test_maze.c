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

#define min_width  5
#define max_width  25
#define min_height 5
#define max_height 25
#define margin     10


bool destroy_maze_does_not_crash_if_passed_null(void){
    destroy_maze(NULL);
    return true;
}

bool destroy_maze_does_not_free_the_maze(void){
    maze_t* maze = malloc(sizeof(maze_t));
    init_maze(500, 500, maze);
    destroy_maze(maze);
    init_maze(400, 400, maze);
    destroy_maze(maze);
    return true;
}

bool init_maze_sets_start_and_end_to_NW_corner_and_SE_corner_respectively(void){
    maze_t maze;
    for(int w = min_width; w <= max_width; w++){
        for(int h = min_height; h <= max_height; h++){
            init_maze(w, h, &maze);
            if(!(maze.end_x == maze.width-1 && maze.end_y == maze.height-1 && maze.start_x == 0 && maze.start_y == 0)){
                return false;
            }
            destroy_maze(&maze);
        }
    }
    return true;
}


bool init_maze_with_width_or_height_less_than_1_sets_it_to_1(void){
    maze_t maze;
    for(int w = 0; w > -25; w--){
        init_maze(w, 5, &maze);
        if(maze.width != 1 || maze.height != 5){
            destroy_maze(&maze);
            return false;
        }
        destroy_maze(&maze);
    }
    for(int h = 0; h>-25; h--){
        init_maze(10, h, &maze);
        if(maze.width != 10 || maze.height != 1){
            destroy_maze(&maze);
            return false;
        }
        destroy_maze(&maze);
    }
    for(int w = 0; w>-25; w--){
        for(int h = 0; h>-25; h--){
            init_maze(w, h, &maze);
            if(maze.width != 1 || maze.height != 1){
                destroy_maze(&maze);
                return false;
            }
            destroy_maze(&maze);
        }
    }
    return true;
}

bool init_maze_respects_size_with_am_minimum_of_1(void){
    maze_t maze;
    for(int w = 1; w <= max_width; w++){
        for(int h = 1; h <= max_height; h++){
            init_maze(w, h, &maze);
            if(!(maze.width == w && maze.height == h)){
                return false;
            }
            destroy_maze(&maze);
        }
    }
    return true;
}

bool init_maze_default_bias_is_1(void){
    maze_t maze;
    init_maze(10, 5, &maze);
    double bias = maze.bias;
    destroy_maze(&maze);
    return bias == (double)1.0;
}


bool set_bias_ignores_value_less_than_or_equal_to_0(void){
    double values[] = {-0.5, -4, -2, -1.5, 0, -0.125, -0, 1};/*>0 terminated*/
    maze_t maze;
    init_maze(10,5,&maze);
    double bias_before = maze.bias;
    for(int i = 0; values[i]<=0; i++){
        set_bias(values[i], &maze);
        if(maze.bias != bias_before){
            destroy_maze(&maze);
            return false;
        }
    }
    destroy_maze(&maze);
    return true;
}

bool set_bias_sets_the_maze_bias_for_values_above_0(void){
    double values[] = {0.5, 4, 2, 1.5, 0.125, 0};/*0 terminated*/
    maze_t maze;
    init_maze(10,5,&maze);
    for(int i = 0; values[i]; i++){
        set_bias(values[i], &maze);
        if(values[i] != maze.bias){
            destroy_maze(&maze);
            return false;
        }
    }
    destroy_maze(&maze);
    return true;
}


bool get_extra_before_init_maze_returns_null(void){
    maze_t maze;
    for(int x = -margin; x < margin; x++){
        for(int y = -margin; y < margin; y++){
            if(get_extra(&maze, x, y)){
                return false;
            }
        }
    }
    return true;
}

bool get_extra_before_setting_extra_size_returns_null(void){
    maze_t maze;
    for(int w = min_width; w <= max_width; w++){
        for(int h = min_height; h <= max_height; h++){
            init_maze(w, h, &maze);
            for(int x = -margin; x < w+margin; x++){
                for(int y = -margin; y < h+margin; y++){
                    if(get_extra(&maze, x, y)){
                        destroy_maze(&maze);
                        return false;
                    }
                }
            }
        }
    }
    destroy_maze(&maze);
    return true;
}

bool get_extra_outside_range_returns_null(void){
    maze_t maze;
    for(int w = min_width; w <= max_width; w++){
        for(int h = min_height; h <= max_height; h++){
            init_maze(w, h, &maze);
            set_size_of_extra(sizeof(int), &maze);
            for(int x = -margin; x < w+margin; x++){
                for(int y = -margin; y < 0; y++){
                    if(get_extra(&maze, x, y)){
                        destroy_maze(&maze);
                        return false;
                    }
                }
                for(int y = h; y < h+margin; y++){
                    if(get_extra(&maze, x, y)){
                        destroy_maze(&maze);
                        return false;
                    }
                }
            }
            
            for(int y = -margin; y < h+margin; y++){
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
        }
    }
    destroy_maze(&maze);
    return true;
}

bool get_extra_returns_to_memory_with_default_value_0(void){
    maze_t maze;
    
    for(int w = min_width; w <= max_width; w++){
        for(int h = min_height; h <= max_height; h++){
            init_maze(w, h, &maze);
            set_size_of_extra(sizeof(int), &maze);
            for(int x = 0; x < w; x++){
                for(int y = 0; y < h; y++){
                    int* t = get_extra(&maze, x, y);
                    if(*t){
                        destroy_maze(&maze);
                        return false;
                    }
                }
            }
        }
    }
    destroy_maze(&maze);
    return true;
}


bool get_extra_returns_a_void_pointer_to_writable_memory(void){
    #define w 25
    #define h 25
    maze_t maze;
    init_maze(w, h, &maze);
    set_size_of_extra(sizeof(int), &maze);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            int* t = get_extra(&maze, x, y);
            *t = ((x+1)<<4)*(y+1);
        }
    }
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
    return true;
    #undef w
    #undef h
}

bool set_size_of_extra_resets_the_contents_of_extra_to_0_regardles_of_old_size(void){
    #define w 25
    #define h 25
    maze_t maze;
    init_maze(w, h, &maze);
    set_size_of_extra(sizeof(uint16_t), &maze);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            uint16_t* t = get_extra(&maze, x, y);
            *t = ((x+1)<<4)*(y+1);
        }
    }
    
    set_size_of_extra(sizeof(uint16_t), &maze);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            uint16_t* t = get_extra(&maze, x, y);
            if(*t){
                destroy_maze(&maze);
                return false;
            }
        }
    }
    
    set_size_of_extra(sizeof(uint32_t), &maze);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            uint32_t* t = get_extra(&maze, x, y);
            if(*t){
                destroy_maze(&maze);
                return false;
            }
        }
    }
    destroy_maze(&maze);
    return true;
    
    #undef w
    #undef h
}

bool get_cell_is_safe_even_far_out_of_bounds(void){
    #define w 25
    #define h 25
    maze_t maze;
    init_maze(w, h, &maze);
    for(int x = -5; x < w+5; x++){
        for(int y = -5; y < h+5; y++){
            volatile cell_t v_cell = get_cell(&maze, x, y);
            cell_t cell = get_cell(&maze, x, y);
            if(!cells_are_equal(v_cell, cell)){
                destroy_maze(&maze);
                return false;
            }
        }
    }
    destroy_maze(&maze);
    return true;
    #undef w
    #undef h
}

bool get_cell_by_default_walls_are_present(void){
    maze_t maze;
    #define w 25
    #define h 25
    init_maze(w, h, &maze);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            cell_t cell = get_cell(&maze, x, y);
            if(!cell.north || !cell.south || !cell.east || !cell.west){
                destroy_maze(&maze);
                return false;
            }
        }
    }
    destroy_maze(&maze);
    #undef w
    #undef h
    return true;
}

bool make_empty_cell_makes_a_cell_that_is_empty(void){
    cell_t cell = make_empty_cell();
    return !(cell.cross_north || 
             cell.cross_west  || 
            cell.north || 
            cell.south || 
            cell.east || 
            cell.west || 
            cell.start || 
            cell.end);
}

bool set_cell_is_safe_even_far_out_of_bounds(void){
    maze_t maze;
    #define w 25
    #define h 25
    init_maze(w, h, &maze);
    for(int x = -5; x < w+5; x++){
        for(int y = -5; y < h+5; y++){
            set_cell(make_empty_cell(), x, y, &maze);
        }
    }
    return true;
    #undef w
    #undef h
}

bool set_cell_handles_horizontal_overlap(void){
    maze_t maze;
    for(int w = 25; w < 35; w++){
        for(int h = 25; h < 35; h++){
            init_maze(w, h, &maze);
            /* h_wall overlap cross_west and north*/
            for(int x = -1; x < w+2; x++){
                for(int y = 1; y < h; y++){
                    if(get_cell(&maze, x, y).cross_west != get_cell(&maze, x-1, y).north){
                        destroy_maze(&maze);
                        return false;
                    }
                    cell_t cell = get_cell(&maze, x, y);
                    cell.north = false;
                    set_cell(cell, x, y, &maze);
                }
            }
            
            /* v_wall overlap west and east*/
            for(int x = 1; x < w; x++){
                for(int y = 0; y < h; y++){
                    if(get_cell(&maze, x, y).west != get_cell(&maze, x-1, y).east){
                        destroy_maze(&maze);
                        return false;
                    }
                    cell_t cell = get_cell(&maze, x, y);
                    cell.east = false;
                    set_cell(cell, x, y, &maze);
                }
            }
            destroy_maze(&maze);
        }
    }
    return true;
}

bool set_cell_handles_vertical_overlap(void){
    maze_t maze;
    for(int w = 25; w < 35; w++){
        for(int h = 25; h < 35; h++){
            init_maze(w, h, &maze);
            /* v_wall overlap cross_north and west*/
            for(int y = -1; y < h+2; y++){
                for(int x = 1; x < w; x++){
                    if(get_cell(&maze, x, y).cross_north != get_cell(&maze, x, y-1).west){
                        destroy_maze(&maze);
                        return false;
                    }
                    cell_t cell = get_cell(&maze, x, y);
                    cell.west = false;
                    set_cell(cell, x, y, &maze);
                }
            }
            
            /* h_wall overlap north and south*/
            for(int y = 1; y < h; y++){
                for(int x = -1; x < w+1; x++){
                    if(get_cell(&maze, x, y).north != get_cell(&maze, x, y-1).south){
                        destroy_maze(&maze);
                        return false;
                    }
                    cell_t cell = get_cell(&maze, x, y);
                    cell.south = false;
                    set_cell(cell, x, y, &maze);
                }
            }
            destroy_maze(&maze);
        }
    }
    return true;
}

bool set_cell_handles_start_and_end(void){
    maze_t maze;
    for(int w = 25; w < 35; w++){
        for(int h = 25; h < 35; h++){
            init_maze(w, h, &maze);
            /* h_wall overlap cross_west and north*/
            for(int x = 0; x < w; x++){
                for(int y = 0; y < h; y++){
                    cell_t cell = get_cell(&maze, x, y);
                    cell.start = true;
                    set_cell(cell, x, y, &maze);
                    if(maze.start_x != x || maze.start_y != y || !get_cell(&maze, x, y).start){
                        destroy_maze(&maze);
                        return false;
                    }
                }
            }
            
            /* v_wall overlap west and east*/
            for(int x = 0; x < w; x++){
                for(int y = 0; y < h; y++){
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
    return true;
}

bool set_cross_handles_horizontal_overlap(void){
    maze_t maze;
    for(int w = 25; w < 35; w++){
        for(int h = 25; h < 35; h++){
            init_maze(w, h, &maze);
            /* h_wall overlap cross_west and north*/
            for(int x = -1; x < w+2; x++){
                for(int y = 1; y < h; y++){
                    if(get_cell(&maze, x, y).cross_west != get_cell(&maze, x-1, y).north){
                        destroy_maze(&maze);
                        return false;
                    }
                    cell_t cell = get_cell(&maze, x, y);
                    cell.north = false;
                    set_cross(cell, x, y, &maze);
                }
            }
            destroy_maze(&maze);
        }
    }
    return true;
}

bool set_cross_handles_vertical_overlap(void){
    maze_t maze;
    for(int w = 25; w < 35; w++){
        for(int h = 25; h < 35; h++){
            init_maze(w, h, &maze);
            /* v_wall overlap cross_north and west*/
            for(int y = -1; y < h+2; y++){
                for(int x = 1; x < w; x++){
                    if(get_cell(&maze, x, y).cross_north != get_cell(&maze, x, y-1).west){
                        destroy_maze(&maze);
                        return false;
                    }
                    cell_t cell = get_cell(&maze, x, y);
                    cell.west = false;
                    set_cross(cell, x, y, &maze);
                }
            }
            destroy_maze(&maze);
        }
    }
    return true;
}


bool set_room_handles_horizontal_overlap(void){
    maze_t maze;
    for(int w = 25; w < 35; w++){
        for(int h = 25; h < 35; h++){
            init_maze(w, h, &maze);
            /* v_wall overlap west and east*/
            for(int x = 1; x < w; x++){
                for(int y = 0; y < h; y++){
                    if(get_cell(&maze, x, y).west != get_cell(&maze, x-1, y).east){
                        destroy_maze(&maze);
                        return false;
                    }
                    cell_t cell = get_cell(&maze, x, y);
                    cell.east = false;
                    set_room(cell, x, y, &maze);
                }
            }
            destroy_maze(&maze);
        }
    }
    return true;
}

bool set_room_handles_vertical_overlap(void){
    maze_t maze;
    for(int w = 25; w < 35; w++){
        for(int h = 25; h < 35; h++){
            init_maze(w, h, &maze);
            /* h_wall overlap north and south*/
            for(int y = 1; y < h; y++){
                for(int x = -1; x < w+1; x++){
                    if(get_cell(&maze, x, y).north != get_cell(&maze, x, y-1).south){
                        destroy_maze(&maze);
                        return false;
                    }
                    cell_t cell = get_cell(&maze, x, y);
                    cell.south = false;
                    set_room(cell, x, y, &maze);
                }
            }
            destroy_maze(&maze);
        }
    }
    return true;
}

/* Takes the name of a function that is passed no arguments, and prints if that function returns true and it's name*/
#define test(f) printf("[%s] " #f "\n", (f())?("\033[0;32mPassed\033[0m"):("\033[0;31mFailed\033[0m"))

int main(){
    
    test(destroy_maze_does_not_crash_if_passed_null);
    test(destroy_maze_does_not_free_the_maze);
    test(init_maze_sets_start_and_end_to_NW_corner_and_SE_corner_respectively);
    test(init_maze_with_width_or_height_less_than_1_sets_it_to_1);
    test(init_maze_respects_size_with_am_minimum_of_1);
    test(init_maze_default_bias_is_1);
    test(set_bias_ignores_value_less_than_or_equal_to_0);
    test(set_bias_sets_the_maze_bias_for_values_above_0);
    test(get_extra_before_init_maze_returns_null);
    test(get_extra_before_setting_extra_size_returns_null);
    test(get_extra_outside_range_returns_null);
    test(get_extra_returns_to_memory_with_default_value_0);
    test(get_extra_returns_a_void_pointer_to_writable_memory);
    test(set_size_of_extra_resets_the_contents_of_extra_to_0_regardles_of_old_size);
    test(make_empty_cell_makes_a_cell_that_is_empty);
    test(get_cell_is_safe_even_far_out_of_bounds);
    test(get_cell_by_default_walls_are_present);
    test(set_cell_is_safe_even_far_out_of_bounds);
    test(set_cell_handles_horizontal_overlap);
    test(set_cell_handles_vertical_overlap);
    test(set_cross_handles_horizontal_overlap);
    test(set_cross_handles_vertical_overlap);
    test(set_room_handles_horizontal_overlap);
    test(set_room_handles_vertical_overlap);
    
    return 0;
}

#undef test

#undef min_width
#undef max_width
#undef min_height
#undef max_height
#undef margin
