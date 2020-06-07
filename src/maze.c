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
    /*Two null terminated arrays of bytes.
      Each byte is a bitmap of walls, 1 is present, 0 is absent*/
    uint8_t **v_walls;
    uint8_t **h_walls;

    /* extra is an array of size_of_extra*width*height bytes,
       broken up into 1 element per cell*/
    size_t size_of_extra;
    void *extra;
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
        if(data->extra){
            free(data->extra);
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
    /*This style of statement calls calloc, stores the pointer,
      and then checks if it was null*/
    if(!(data->v_walls = calloc(height+1, sizeof(uint8_t*)))){
        delete_maze_data(data);
        return NULL;
    }
    if(!(data->h_walls = calloc(height, sizeof(uint8_t*)))){
        delete_maze_data(data);
        return NULL;
    }

    data->size_of_extra = (size_t)0;
    data->extra = NULL;

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

int set_size_of_extra(size_t new_size, maze_t* maze){
    if(maze->data->extra){
        free(maze->data->extra);
    }
    maze->data->extra = calloc(new_size, maze->width * maze->height);
    if(maze->data->extra){
        maze->data->size_of_extra = new_size;
        return 0;
    }
    return -1;
}

int init_maze(int width, int height, maze_t *maze){
    if(!maze){
        return -1;
    }
    if(width < 1){
        width = 1;
    }
    if(height < 1){
        height = 1;
    }
    maze->width = width;
    maze->height = height;
    maze->start_x = 0;
    maze->start_y = 0;
    maze->end_x = width-1;
    maze->end_y = height-1;
    maze->bias = (double)1.0;
    maze->data = new_maze_data(width, height);
    return (maze->data)?(0):(-1);
}

int destroy_maze(maze_t *maze){
    if(maze){
        delete_maze_data(maze->data);
        maze->data = NULL;
    }
    return 0;
}

void set_bias(double bias, maze_t *maze){
    if(bias > 0){
        maze->bias = bias;
    }
}

__attribute__ ((const)) inline static bool
  cross_north_outside_maze(const int x, const int y, const int width, const int height){
    return y <= 0 || y >  height || x <  0 || x >  width;
}
__attribute__ ((const)) inline static bool
  cross_north_inside_maze(const int x, const int y, const int width, const int height){
    return y >  0 && y <= height && x > 0 && x < width;
}

__attribute__ ((const)) inline static bool
  cross_west_outside_maze(const int x, const int y, const int width, const int height){
    return y <  0 || y >  height || x <= 0 || x >  width;
}
__attribute__ ((const)) inline static bool
  cross_west_inside_maze(const int x, const int y, const int width, const int height){
    return y >  0 && y <  height && x >  0 && x <= width;
}

__attribute__ ((const)) inline static bool
  west_outside_maze(const int x, const int y, const int width, const int height){
    return y <  0 || y >= height || x <  0 || x >  width ;
}
__attribute__ ((const)) inline static bool
  west_inside_maze(const int x, const int y, const int width, const int height){
    return y >= 0 && y <  height && x >  0 && x <  width ;
}


__attribute__ ((const)) inline static bool
  north_outside_maze(const int x, const int y, const int width, const int height){
    return y <  0 || y >  height || x <  0 || x >= width;
}
__attribute__ ((const)) inline static bool
  north_inside_maze(const int x, const int y, const int width, const int height){
    return y >  0 && y <  height && x >= 0 && x <  width;
}


__attribute__ ((const)) inline static bool
  east_outside_maze(const int x, const int y, const int width, const int height){
    return y <  0 || y >= height || x < -1 || x >= width;
}
__attribute__ ((const)) inline static bool
  east_inside_maze(const int x, const int y, const int width, const int height){
    return y >= 0 && y <  height && x > -1 && x <  width-1;
}

__attribute__ ((const)) inline static bool
  south_outside_maze(const int x, const int y, const int width, const int height){
    return y < -1 || y >= height || x <  0 || x >= width;
}
__attribute__ ((const)) inline static bool
  south_inside_maze(const int x, const int y, const int width, const int height){
    return y > -1 && y <height-1 && x >= 0 && x <  width;
}


__attribute__ ((pure)) cell_t get_cell(maze_t *maze, int x, int y){
    cell_t cell;
    int w = maze->width;
    int h = maze->height;

    cell.cross_north = !cross_north_outside_maze(x, y, w, h) &&
        (!cross_north_inside_maze(x, y, w, h) ||
        (maze->data->v_walls[y-1])[index_of_wall(x-1)] & mask_for_wall(x-1) );

    cell.cross_west  = !cross_west_outside_maze(x, y, w, h) &&
        (! cross_west_inside_maze(x, y, w, h) ||
        (maze->data->h_walls[y-1])[index_of_wall(x-1)] & mask_for_wall(x-1) );

    cell.west        = !west_outside_maze(x, y, w, h) &&
        (      ! west_inside_maze(x, y, w, h) ||
        (maze->data->v_walls[y  ])[index_of_wall(x-1)] & mask_for_wall(x-1) );

    cell.north       = !north_outside_maze(x, y, w, h) &&
        (      !north_inside_maze(x, y, w, h) ||
        (maze->data->h_walls[y-1])[index_of_wall(x  )] & mask_for_wall(x  ) );

    cell.east        = !east_outside_maze(x, y, w, h) &&
        (      ! east_inside_maze(x, y, w, h) ||
        (maze->data->v_walls[y  ])[index_of_wall(x  )] & mask_for_wall(x  ) );

    cell.south       = !south_outside_maze(x, y, w, h) &&
        (      !south_inside_maze(x, y, w, h) ||
        (maze->data->h_walls[y  ])[index_of_wall(x  )] & mask_for_wall(x  ) );

    cell.start = maze->start_x == x && maze->start_y == y;
    cell.end   = maze->end_x   == x && maze->end_y   == y;

    return cell;
}

__attribute__ ((pure)) void* get_extra(maze_t* maze, int x, int y){
    if(!maze || !maze->data ||  x < 0 || x >= maze->width || y < 0 || y >= maze->height){
        return NULL;
    }else{
        return maze->data->extra+(maze->data->size_of_extra * (maze->width * y + x));
    }
}

static inline void set_v_wall(bool val, int x, int y, maze_t *maze){
    if(east_inside_maze(x, y, maze->width, maze->height)){
        if(val){
            (maze->data->v_walls[y])[index_of_wall(x)] |=  mask_for_wall(x);
        }else{
            (maze->data->v_walls[y])[index_of_wall(x)] &= ~mask_for_wall(x);
        }
    }
}

static inline void set_h_wall(bool val, int x, int y, maze_t *maze){
    if(south_inside_maze(x, y, maze->width, maze->height)){
        if(val){
            (maze->data->h_walls[y])[index_of_wall(x)] |=  mask_for_wall(x);
        }else{
            (maze->data->h_walls[y])[index_of_wall(x)] &= ~mask_for_wall(x);
        }
    }
}


void set_room(cell_t cell, int x, int y, maze_t *maze){
    set_h_wall(cell.north, x,   y-1, maze);
    set_v_wall(cell.west , x-1, y,   maze);
    set_h_wall(cell.south, x,   y,   maze);
    set_v_wall(cell.east , x,   y,   maze);
    return;
}

void set_cross(cell_t cell, int x, int y, maze_t *maze){
    set_v_wall(cell.cross_north, x-1, y-1, maze);
    set_h_wall(cell.cross_west,  x-1, y-1, maze);
    set_v_wall(cell.west,        x-1, y,   maze);
    set_h_wall(cell.north,       x,   y-1, maze);
    return;
}

void set_cell(cell_t cell, int x, int y, maze_t *maze){
    set_v_wall(cell.cross_north, x-1, y-1, maze);
    set_h_wall(cell.cross_west,  x-1, y-1, maze);
    set_v_wall(cell.west,        x-1, y,   maze);
    set_h_wall(cell.north,       x,   y-1, maze);
    set_v_wall(cell.east ,       x,   y,   maze);
    set_h_wall(cell.south,       x,   y,   maze);

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

__attribute__ ((const)) cell_t make_empty_cell(void){
    return (cell_t){
        .cross_north = 0,
        .cross_west  = 0,
        .west        = 0,
        .north       = 0,
        .east        = 0,
        .south       = 0,
        .start       = 0,
        .end         = 0};
}

__attribute__ ((const)) bool cells_are_equal(cell_t a, cell_t b){
    return
        a.cross_north == b.cross_north &&
        a.cross_west  == b.cross_west  &&
        a.west        == b.west &&
        a.north       == b.north &&
        a.east        == b.east &&
        a.south       == b.south &&
        a.start       == b.start &&
        a.end         == b.end;

}

#undef width_bytes
#undef index_of_wall
#undef mask_for_wall
