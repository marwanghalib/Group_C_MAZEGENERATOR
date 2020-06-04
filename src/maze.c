#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif


#ifndef STDDEF_H
#define STDDEF_H
#include <stddef.h>
#endif

#ifndef MAZE_H
#define MAZE_H
#include <maze.h>
#endif

#define width_bytes(w) ((((w)-1)>>3)+1)
#define index_of_wall(x) ((x)>>3)
#define mask_for_wall(x) (((uint8_t)1)<<((x)&0b00000111))

struct maze_data{
    /*Two null terminated arrays of bytes. Each byte is a bitmap of walls, 1 is present, 0 is absent*/
    uint8_t **v_walls;
    uint8_t **h_walls;
};

static int delete_maze_data(struct maze_data* data){
    if(data){
        if(data->v_walls){
            for(int i = 0; data->v_walls[i]; i++){
                free(data->v_walls[i]);
            }
            free(data->v_walls);
        }
        if(data->h_walls){
            for(int i = 0; data->h_walls[i]; i++){
                free(data->h_walls[i]);
            }
            free(data->h_walls);
        }
        free(data);
    }
    return 0;
}



static struct maze_data* new_maze_data(int width, int height){
    struct maze_data *data = calloc(1, sizeof(struct maze_data));
    if(!data){/*If malloc failed, there is not much we can do.*/
        return NULL;
    }
    /*This calls calloc, stores the pointer, and then checks if it was null*/
    if(!(data->v_walls = calloc(height+1, sizeof(uint8_t*)))){
        delete_maze_data(data);
        return NULL;
    }
    if(!(data->h_walls = calloc(height, sizeof(uint8_t*)))){
        delete_maze_data(data);
        return NULL;
    }

    for(int y = 0; y<height; y++){
        if(!(data->v_walls[y] = malloc(sizeof(uint8_t) * width_bytes(width-1)))){
            delete_maze_data(data);
            return NULL;
        }else{
            for(int x = 0; x<width_bytes(width-1); x++){
                ((data->v_walls)[y])[x] = 0xFF;
            }
        }
    }

    for(int y = 0; y<height-1; y++){
        if(!(data->h_walls[y] = malloc(sizeof(uint8_t) * width_bytes(width)))){
            delete_maze_data(data);
            return NULL;
        }else{
            for(int x = 0; x<width_bytes(width); x++){
                ((data->h_walls)[y])[x] = 0xFF;
            }
        }
    }
    return data;
}

//typedef struct maze maze_t;

int init_maze(int width, int height, maze_t *maze){
    maze->width = width;
    maze->height = height;
    maze->start_x = 0;
    maze->start_y = 0;
    maze->end_x = width-1;
    maze->end_y = height-1;
    maze->bias = (double)0.0;

    maze->data = new_maze_data(width, height);

    return (maze->data)?(0):(-1);
}


int destroy_maze(maze_t *maze){
    delete_maze_data(maze->data);
    return 0;
}

void set_bias(double bias, maze_t *maze){
    maze->bias = bias;
}

cell_t get_cell(maze_t *maze, int x, int y){
    cell_t cell = (cell_t){.mask = 0};

    cell.wall_east  = (x < maze->width-1)  && ((y<0) || (y>=maze->height-1) ||
        ((maze->data->h_walls[y  ])[index_of_wall(x+1)]&mask_for_wall(x+1)));
    cell.wall_south = (y < maze->height-1) && ((x<0) || (x>=maze->width-1) ||
        ((maze->data->v_walls[y+1])[index_of_wall(x  )]&mask_for_wall(x  )));

    cell.wall_west  = (x >= 0) && ((y < 0) || (y>=maze->height-1) ||
        ((maze->data->h_walls[y  ])[index_of_wall(x  )]&mask_for_wall(x  )));
    cell.wall_north = (y >= 0) && ((x < 0) || (x >= maze->width-1) ||
        ((maze->data->v_walls[y  ])[index_of_wall(x  )]&mask_for_wall(x  )));

    cell.door_west  = (x >= 0) && (y >= 0) && ((y == 0) ||
        ((maze->data->h_walls[y  ])[index_of_wall(x-1)]&mask_for_wall(x-1)));
    cell.door_north = (x >= 0) && (y >= 0) && ((x == 0) ||
        ((maze->data->v_walls[y-1])[index_of_wall(x  )]&mask_for_wall(x  )));

    cell.start = maze->start_x == x && maze->start_y == y;
    cell.end   = maze->end_x   == x && maze->end_y   == y;
    return cell;
}

static inline void set_wall_east(cell_t cell, int x, int y, maze_t *maze){
    if(y >= 0 && y < maze->height-1 && x < maze->width-1){
        if(cell.wall_east){
            (maze->data->h_walls[y])[index_of_wall(x+1)] |=  mask_for_wall(x+1);
        }else{
            (maze->data->h_walls[y])[index_of_wall(x+1)] &= ~mask_for_wall(x+1);
        }
    }
}

static inline void set_wall_south(cell_t cell, int x, int y, maze_t *maze){
    if(x >= 0 && x < maze->width-1 && y < maze->height-1){
        if(cell.wall_south){
            (maze->data->v_walls[y+1])[index_of_wall(x)] |=  mask_for_wall(x);
        }else{
            (maze->data->v_walls[y+1])[index_of_wall(x)] &= ~mask_for_wall(x);
        }
    }
}

static inline void set_wall_west(cell_t cell, int x, int y, maze_t *maze){
    if(x >= 0 && y >= 0 && y < maze->width-1){
        if(cell.wall_west){
            (maze->data->h_walls[y])[index_of_wall(x-1)] |=  mask_for_wall(x-1);
        }else{
            (maze->data->h_walls[y])[index_of_wall(x-1)] &= ~mask_for_wall(x-1);
        }
    }
}


static inline void set_wall_north(cell_t cell, int x, int y, maze_t *maze){
    if(x >= 0 && y >= 0 && x < maze->width-1){
        if(cell.wall_north){
            (maze->data->v_walls[y-1])[index_of_wall(x)] |=  mask_for_wall(x);
        }else{
            (maze->data->v_walls[y-1])[index_of_wall(x)] &= ~mask_for_wall(x);
        }
    }
}

static inline void set_door_north(cell_t cell, int x, int y, maze_t *maze){
    if(x >= 0 && y >= 0 && y > 0){
        if(cell.door_north){
            (maze->data->h_walls[y-1])[index_of_wall(x)] |=  mask_for_wall(x);
        }else{
            (maze->data->h_walls[y-1])[index_of_wall(x)] &= ~mask_for_wall(x);
        }
    }
}

static inline void set_door_west(cell_t cell, int x, int y, maze_t *maze){
    if(x >= 0 && y >= 0 && x > 0){
        if(cell.wall_north){
            (maze->data->v_walls[y])[index_of_wall(x-1)] |=  mask_for_wall(x-1);
        }else{
            (maze->data->v_walls[y])[index_of_wall(x-1)] &= ~mask_for_wall(x-1);
        }
    }
}


void set_door(cell_t cell, int x, int y, maze_t *maze){
    set_door_west(cell, x, y, maze);
    set_door_north(cell, x, y, maze);
    set_wall_north(cell, x, y, maze);
    set_wall_west(cell, x, y, maze);
    return;
}

void set_walls(cell_t cell, int x, int y, maze_t *maze){
    set_wall_east(cell, x, y, maze);
    set_wall_south(cell, x, y, maze);
    set_wall_west(cell, x, y, maze);
    set_wall_north(cell, x, y, maze);
    return;
}

void set_cell(cell_t cell, int x, int y, maze_t *maze){
    set_door_west(cell, x, y, maze);
    set_door_north(cell, x, y, maze);
    set_wall_east(cell, x, y, maze);
    set_wall_south(cell, x, y, maze);
    set_wall_west(cell, x, y, maze);
    set_wall_north(cell, x, y, maze);
    if(cell.start){
        maze->start_x = x;
        maze->start_y = y;
    }
    if(cell.end){
        maze->end_x = x;
        maze->end_y = y;
    }
    return;
}

cell_t make_empty_cell(void){
    return (cell_t){
        .mask       = 0,
        .wall_east  = 0,
        .wall_south = 0,
        .wall_west  = 0,
        .wall_north = 0,
        .door_north = 0,
        .door_west  = 0,
        .start      = 0,
        .end        = 0};
}

#undef width_bytes
#undef index_of_wall
#undef mask_for_wall
